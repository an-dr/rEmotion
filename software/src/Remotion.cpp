// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"

#include "Remotion.hpp"

const RemotionStatus Remotion::start(const std::string &port_name, int video_source)
{
    _port_name = port_name;
    _video_source = video_source;
    
        
    for (_video_source; _video_source < _video_source + 3; _video_source++)
    {
        _cap.open(_video_source);
        if (!_cap.isOpened())
        {
            _status.cameraError = RemotionError::ERROR_OPEN_PORT;
            printf("Error: Could not open video stream n %d\n", _video_source);
        } else {
            _status.cameraError = RemotionError::NO_ERROR;
            break;
        }
    }

    
    _serialPort.SetDevice(_port_name);
    _serialPort.SetBaudRate(mn::CppLinuxSerial::BaudRate::B_9600);
    _serialPort.SetParity(mn::CppLinuxSerial::Parity::NONE);
    _serialPort.SetNumStopBits(mn::CppLinuxSerial::NumStopBits::ONE);
    _serialPort.SetNumDataBits(mn::CppLinuxSerial::NumDataBits::EIGHT);
    _serialPort.SetTimeout(100);
    _serialPort.Open();
    
    _serialPort.Write("3"); // tmp
    
    return getStatus();
}

cv::Mat Remotion::readImage(RemotionError *error_buff)
{
    auto img = cv::Mat();
    if (!_cap.isOpened())  // check if we succeeded
        throw std::runtime_error("Could not open video stream");
    _cap >> img;
    return img;
}

RemotionError Remotion::setExpression(RemotionExpression exp)
{
    switch (exp)
    {
    case RemotionExpression::HAPPY:
        _serialPort.Write("1");
        break;
    case RemotionExpression::CALM:
        _serialPort.Write("2");
        break;
    case RemotionExpression::SAD:
        _serialPort.Write("3");
        break;
    case RemotionExpression::ANGRY:
        _serialPort.Write("4");
        break;
    default:
        break;
    }
    return RemotionError();
}

RemotionStatus Remotion::getStatus() const
{
    return _status;
}
