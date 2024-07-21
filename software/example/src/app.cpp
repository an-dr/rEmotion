// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "Remotion.hpp"

int main(int argc, char const *argv[]) {
    Remotion r;
    r.start("/dev/ttyUSB0", 0);

    const int width = 640;
    const int height = 480;
    size_t out_size = 0;
    std::string video_dev = "/dev/video0";
    
    auto err = r.createVideoCapture(video_dev, width, height, 30);
    if (err != RemotionError::NO_ERROR) {
        std::cerr << "Error: " << static_cast<int>(err) << std::endl;
        return 1;
    }
    
    char buffer[2 * width * height] = {};
    // while (true) {
        // r.setExpression(RemotionExpression::HAPPY);
        // sleep(1);
        // r.setExpression(RemotionExpression::CALM);
        // sleep(1);
        
        r.readVideoFrame(buffer, out_size);
        cv::Mat image(cv::Size(width, height), CV_8UC2, buffer);
        cv::cvtColor(image, image, cv::COLOR_YUV2BGR_YUYV);
        
        cv::imwrite("img.jpg", image);
        // cv::imshow("img", img);
        // cv::waitKey(1);
    // }

    /* code */
    return 0;
}
