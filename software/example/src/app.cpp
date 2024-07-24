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
#include <unistd.h>
#include "Remotion.hpp"

static void write_img(char *buffer, int width, int height,
                      std::string filename) {
    cv::Mat img(cv::Size(width, height), CV_8UC2, buffer);
    cv::cvtColor(img, img, cv::COLOR_YUV2BGR_YUYV);
    cv::imwrite(filename, img);
}

int main(int argc, char const *argv[]) {
    // Set parameters
    const int width = 1280;
    const int height = 720;
    const int fps = 30;
    const unsigned int format = V4L2_PIX_FMT_YUYV;
    std::string video_dev = "/dev/video0";
    std::string port_name = "/dev/ttyUSB0";

    // Create and init Remotion object
    Remotion r;
    auto buffer_size = r.getVideoCaptureBufferSize();
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
