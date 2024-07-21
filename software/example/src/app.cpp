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
    const int width = 1280;
    const int height = 720;
    const int fps = 30;
    std::string video_dev = "/dev/video0";

    Remotion r;
    r.start("/dev/ttyUSB0", "/dev/video0", V4L2_PIX_FMT_YUYV, 1280, 720, 30);

    int buffer_size = r.getVideoCaptureBufferSize();
    char *buffer = new char[r.getVideoCaptureBufferSize()];

    r.setExpression(RemotionExpression::HAPPY);
    sleep(1);
    r.setExpression(RemotionExpression::CALM);
    sleep(1);
    while (true) {
        r.readVideoFrame(buffer, buffer_size);
        write_img(buffer, width, height, "img.jpg");
        sleep(1 / fps);
    }

    /* code */
    return 0;
}
