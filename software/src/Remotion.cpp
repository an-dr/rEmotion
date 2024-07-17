// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <cstdio>
#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

#include "CppLinuxSerial/SerialPort.hpp"
#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"
#include "V4l2Capture.h"

#include "Remotion.hpp"

Remotion::~Remotion() { stop(); }

const RemotionStatus Remotion::start(const std::string &port_name,
                                     int video_source) {
    _port_name = port_name;
    _video_source = video_source;

    _serialPort.SetDevice(_port_name);
    _serialPort.SetBaudRate(mn::CppLinuxSerial::BaudRate::B_9600);
    _serialPort.SetParity(mn::CppLinuxSerial::Parity::NONE);
    _serialPort.SetNumStopBits(mn::CppLinuxSerial::NumStopBits::ONE);
    _serialPort.SetNumDataBits(mn::CppLinuxSerial::NumDataBits::EIGHT);
    _serialPort.SetTimeout(SERIAL_PORT_TIMEOUT);
    _serialPort.Open();

    return getStatus();
}

void Remotion::stop() {
    _serialPort.Close();
    _cap.release();
}

cv::Mat Remotion::readImage(RemotionError *error_buff) {
    auto img = cv::Mat();
    if (tryToOpenCamera() != RemotionError::NO_ERROR)  // check if we succeeded
        throw std::runtime_error("Could not open video stream");
    _cap >> img;
    return img;
}

RemotionError Remotion::setExpression(RemotionExpression exp) {
    switch (exp) {
    case RemotionExpression::CALM:
        _serialPort.Write("0");
        break;
    case RemotionExpression::BLINK:
        _serialPort.Write("1");
        break;
    case RemotionExpression::ANGRY:
        _serialPort.Write("2");
        break;
    case RemotionExpression::HAPPY:
        _serialPort.Write("3");
        break;
    case RemotionExpression::SAD:
        _serialPort.Write("4");
        break;
    case RemotionExpression::DUNNO:
        _serialPort.Write("5");
        break;
    case RemotionExpression::CONFUSED:
        _serialPort.Write("6");
        break;
    case RemotionExpression::THINKING:
        _serialPort.Write("7");
        break;
    default:
        break;
    }
    return RemotionError();
}

RemotionStatus Remotion::getStatus() const { return _status; }

RemotionError Remotion::tryToOpenCamera() {
    _cap.open(_video_source);
    if (!_cap.isOpened()) {
        _status.cameraError = RemotionError::ERROR_OPEN_PORT;
        throw std::runtime_error("Could not open video stream No. " +
                                 std::to_string(_video_source));
    } else {
        _status.cameraError = RemotionError::NO_ERROR;
    }
    return _status.cameraError;
}

RemotionError Remotion::createVideoCapture(std::string &device, int width,
                                           int height, int fps) {
    return RemotionError();
}

RemotionError Remotion::createVideoCapture(std::string &device, int width,
                                           int height, int fps) {
    V4L2DeviceParameters param(device, V4L2_PIX_FMT_VP8, width, height, fps,
                               IOTYPE_READWRITE, 0);
    _videoCapture = V4l2Capture::create(param);
    if (_videoCapture == NULL)
	{	
		// LOG(WARN) << "Cannot reading from V4L2 capture interface for device:" << in_devname; 
        return RemotionError::ERROR_OPEN_PORT;
	}
    return RemotionError::NO_ERROR;
    
}
