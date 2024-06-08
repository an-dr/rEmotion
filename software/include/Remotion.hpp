// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"

class Remotion
{
public:
    RemotionError start(std::string port_name, int video_source);
    cv::Mat readImage(RemotionError *error_buff = nullptr);
    RemotionError setExpression(RemotionExpression exp);
    RemotionStatus getStatus();
    
private:
    RemotionStatus status;
    std::string port_name;
    int video_source;
    cv::VideoCapture cap;
};
