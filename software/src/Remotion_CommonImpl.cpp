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
                                     const std::string &video_device,
                                     unsigned int v4l2_pix_fmt, int width,
                                     int height, int fps) {
    _port_name = port_name;
    _videoCaptureParams = {video_device, v4l2_pix_fmt, width, height, fps};
    return getStatus();
}

void Remotion::stop() {
    delete _serialPort;
    delete _videoCapture;
}

RemotionStatus Remotion::getStatus() const { return _status; }
