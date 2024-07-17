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

    while (true) {
        r.setExpression(RemotionExpression::HAPPY);
        sleep(1);
        r.setExpression(RemotionExpression::CALM);
        sleep(1);

        auto img = r.readImage(nullptr);
        cv::imwrite("img.jpg", img);
        cv::imshow("img", img);
        cv::waitKey(1);
    }

    /* code */
    return 0;
}
