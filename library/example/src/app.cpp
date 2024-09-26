// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <linux/videodev2.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#include "RemotionCamera.hpp"
#include "RemotionController.hpp"

static void write_img(char *buffer, int width, int height,
                      std::string filename) {
    cv::Mat img = cv::imdecode(
        cv::Mat(1, width * height * 3 / 2, CV_8UC1, buffer), cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Failed to decode image" << std::endl;
        return;
    }
    cv::imwrite(filename, img);
}

uint64_t getMillis() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
}

int main(int argc, char const *argv[]) {
    (void)argc;
    (void)argv;

    // Set parameters
    const int width = 1280;
    const int height = 720;
    const int fps = 30;
    std::string video_dev = "/dev/video0";
    std::string port_name = "/dev/ttyACM0";
    const unsigned int format = V4L2_PIX_FMT_MJPEG;
    // check the format via `v4l2-ctl --list-formats-ext`

    // Create and init RemotionCamera object and video buffer
    Re::RemotionCamera cam(video_dev, format, width, height, fps);
    auto vidbuf_size = cam.getVideoCaptureBufferSize();
    if (vidbuf_size == -1) {
        return -1;
    }
    char *vidbuf = new char[vidbuf_size];

    // Create and init RemotionController object
    Re::RemotionController ctrl(port_name);
    ctrl.setExpression(RemotionExpression::CONFUSED);
    sleep(1);
    ctrl.setExpression(RemotionExpression::CALM);
    sleep(1);
    ctrl.setExpression(RemotionExpression::HAPPY);
    sleep(1);

    // Move the robot every 5 seconds, read video frames and save them to
    // img.jpg continuously
    uint64_t last_move = 0;
    uint64_t move_period_ms = 3000;
    auto move = RemotionMovement::LEFT;
    auto expression = RemotionExpression::HAPPY;
    // Read video frames and save them to img.jpg
    while (true) {
        cam.readVideoFrame(vidbuf, vidbuf_size);
        write_img(vidbuf, width, height, "img.jpg");
        sleep(1 / fps);  // sleep for 1/fps seconds otherwise the video frames
                         // will go not in real time
        if (getMillis() - last_move > move_period_ms) {
            // Move
            ctrl.setMovement(move);
            ctrl.setExpression(expression);
            // Change direction and expression
            move = (move == RemotionMovement::LEFT) ? RemotionMovement::RIGHT
                                                    : RemotionMovement::LEFT;
            expression = (expression == RemotionExpression::HAPPY)
                             ? RemotionExpression::ANGRY
                             : RemotionExpression::HAPPY;
            // Store update time
            last_move = getMillis();
            std::cout << "Move! Time: " << last_move << std::endl;
        }
    }
}
