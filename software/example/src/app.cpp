// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "Remotion.hpp"

int main(int argc, char const *argv[])
{
    Remotion r;
    r.start("/dev/ttyUSB0", 0);
    
    while (true)
    {
        auto img = r.readImage(nullptr);
        cv::imshow("img", img);
        sleep(1);
        
        r.setExpression(RemotionExpression::HAPPY);
        sleep(1);
        r.setExpression(RemotionExpression::CALM);
        sleep(1);
        
    }
    
    
    /* code */
    return 0;
}
