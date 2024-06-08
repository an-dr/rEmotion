// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <string>
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
    
    _cap.open(_video_source);
    if (!_cap.isOpened())
    {
        _status.cameraError = RemotionError::ERROR_OPEN_PORT;
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
    return img;
}

RemotionError Remotion::setExpression(RemotionExpression exp)
{
    return RemotionError();
}

RemotionStatus Remotion::getStatus() const
{
    return _status;
}
