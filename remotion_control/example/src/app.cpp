// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <cstdlib>
#include <iostream>
#include <jpeglib.h>
#include <linux/videodev2.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "RemotionCamera.hpp"
#include "RemotionController.hpp"

void my_error_exit(j_common_ptr cinfo) {
    (void)cinfo;
    // You can log the error or handle it as needed
    // But do not call exit() to suppress the warning
}

static cv::Mat extract_frame_from_mjpeg(unsigned char *mjpeg_data, int width,
                                        int height) {
    // Error handling
    jpeg_error_mgr jerr;
    jerr.error_exit = my_error_exit;

    // Create a new jpeg_decompress_struct object
    jpeg_decompress_struct cinfo;

    // Suppress warnings
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

    // Create a new cv::Mat object with the same size and number of channels as
    // the output image
    cv::Mat frame(height, width, CV_8UC3);

    // Copy the pixel data from the jpeg_decompress_struct object to the cv::Mat
    // object
    JSAMPROW row_pointer[1];
    int row_stride = width * 3;
    while (cinfo.output_scanline < cinfo.output_height) {
        row_pointer[0] =
            (JSAMPROW)frame.data + cinfo.output_scanline * row_stride;
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Clean up the jpeg_decompress_struct object
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    // Convert mat color space from BGR to RGB
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    // Return the cv::Mat object
    return frame;
}

static void write_img(char *buffer, int width, int height,
                      std::string filename) {
    // decode mjpg buffer
    cv::Mat img =
        extract_frame_from_mjpeg((unsigned char *)buffer, width, height);

    // cv::Mat img = cv::imdecode(cv::Mat(1, width * height * 3 / 2, CV_8UC1,
    // buffer), cv::IMREAD_COLOR);
    cv::imwrite(filename, img);
}

int main(int argc, char const *argv[]) {
    (void)argc;
    (void)argv;

    // Set parameters
    const int width = 640;
    const int height = 480;
    const int fps = 30;
    const unsigned int format =
        V4L2_PIX_FMT_MJPEG;  // check via v4l2-ctl --list-formats-ext
    std::string video_dev = "/dev/video0";
    std::string port_name = "/dev/ttyACM0";

    Re::RemotionCamera cam(video_dev, format, width, height, fps);
    auto vidbuf_size = cam.getVideoCaptureBufferSize();
    if (vidbuf_size == -1) {
        return -1;
    }
    char *vidbuf = new char[vidbuf_size];

    // Create and init Remotion object
    Re::RemotionController ctrl(port_name);
    ctrl.setExpression(RemotionExpression::CONFUSED);
    sleep(1);
    ctrl.setExpression(RemotionExpression::CALM);
    sleep(1);
    ctrl.setExpression(RemotionExpression::HAPPY);
    sleep(1);

    // Read video frames and save them to img.jpg
    while (true) {
        cam.readVideoFrame(vidbuf, vidbuf_size);
        write_img(vidbuf, width, height, "img.jpg");
        sleep(1 / fps);
    }
}
