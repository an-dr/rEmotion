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

#include "CppLinuxSerial/SerialPort.hpp"
#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"

class Remotion
{
public:
    Remotion() = default;
    ~Remotion();
    const RemotionStatus start(const std::string &port_name, int video_source);
    void stop();
    cv::Mat readImage(RemotionError *error_buff = nullptr);
    RemotionError setExpression(RemotionExpression exp);
    RemotionStatus getStatus() const;

private:
    RemotionError tryToOpenCamera();

    mn::CppLinuxSerial::SerialPort _serialPort = mn::CppLinuxSerial::SerialPort();
    RemotionStatus _status = RemotionStatus();
    std::string _port_name = "";
    int _video_source = -1;
    cv::VideoCapture _cap = cv::VideoCapture();
};
