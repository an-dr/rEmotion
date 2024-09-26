// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <linux/videodev2.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <jpeglib.h>
#include <unistd.h>
#include "Remotion.hpp"


static cv::Mat extract_frame_from_mjpeg(unsigned char* mjpeg_data, int width, int height)
{
    // Create a new jpeg_decompress_struct object
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);

    // Initialize the jpeg_decompress_struct object
    jpeg_create_decompress(&cinfo);

    // Set the source data for the jpeg_decompress_struct object
    jpeg_mem_src(&cinfo, mjpeg_data, width * height * 3 / 2);

    // Read the header information for the jpeg data
    jpeg_read_header(&cinfo, TRUE);

    // Set the output image dimensions and color space
    cinfo.output_width = width;
    cinfo.output_height = height;
    cinfo.output_components = 3;
    cinfo.out_color_space = JCS_RGB;

    // Allocate memory for the output image
    jpeg_start_decompress(&cinfo);

    // Create a new cv::Mat object with the same size and number of channels as the output image
    cv::Mat frame(height, width, CV_8UC3);

    // Copy the pixel data from the jpeg_decompress_struct object to the cv::Mat object
    JSAMPROW row_pointer[1];
    int row_stride = width * 3;
    while (cinfo.output_scanline < cinfo.output_height)
    {
        row_pointer[0] = (JSAMPROW)frame.data + cinfo.output_scanline * row_stride;
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Clean up the jpeg_decompress_struct object
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    // Return the cv::Mat object
    return frame;
}

static void write_img(char *buffer, int width, int height,
                      std::string filename) {
    cv::Mat img = extract_frame_from_mjpeg((unsigned char *)buffer, width, height);
    cv::imwrite(filename, img);
    // cv::imwrite(filename, img);
}


int main(int argc, char const *argv[]) {
    // Set parameters
    const int width = 1280;
    const int height = 720;
    const int fps = 30;
    const unsigned int format = V4L2_PIX_FMT_MJPEG; // check via v4l2-ctl --list-formats-ext
    std::string video_dev = "/dev/video0";
    std::string port_name = "/dev/ttyACM0";

    // Create and init Remotion object
    Remotion r;
    auto buffer_size = r.getVideoCaptureBufferSize( video_dev, format, width, height, fps);
    if (buffer_size == -1) {
        return -1;
    }
    char *buffer = new char[buffer_size];
    r.start(port_name, video_dev, format, width, height, fps);


    // Set different expressions
    r.setExpression(RemotionExpression::CONFUSED);
    sleep(1);
    r.setExpression(RemotionExpression::CALM);
    sleep(1);
    r.setExpression(RemotionExpression::HAPPY);
    sleep(1);
    
    // Read video frames and save them to img.jpg
    while (true) {
        r.readVideoFrame(buffer, buffer_size);
        write_img(buffer, width, height, "img.jpg");
        sleep(1 / fps);
    }
    
    r.stop();
    delete buffer;
    return -1;
}
