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

class Remotion {
 public:
    Remotion() = default;
    Remotion(Remotion &&) = delete;
    Remotion(const Remotion &) = delete;
    Remotion &operator=(const Remotion &) = delete;
    Remotion &operator=(Remotion &&) = delete;
    ~Remotion();

    /// @brief Start Remotion camera
    /// @param port_name - serial port name, e.g. "/dev/ttyUSB0"
    /// @param video_source - video source number
    /// @return RemotionStatus
    const RemotionStatus start(const std::string &port_name, int video_source);
    
    /// @brief Stop Remotion camera
    void stop();
    
    /// @brief Read image from camera
    /// @param error_buff - error buffer
    /// @return  cv::Mat
    cv::Mat readImage(RemotionError *error_buff = nullptr);
    
    /// @brief Set expression
    /// @param exp - expression
    /// @return RemotionError
    RemotionError setExpression(RemotionExpression exp);
    
    /// @brief Get status
    /// @return RemotionStatus
    [[nodiscard]] RemotionStatus getStatus() const;

 private:
    constexpr static int SERIAL_PORT_TIMEOUT = 100;
 
    RemotionError tryToOpenCamera();

    mn::CppLinuxSerial::SerialPort _serialPort =
        mn::CppLinuxSerial::SerialPort();
    RemotionStatus _status = RemotionStatus();
    std::string _port_name = "";
    int _video_source = -1;
    cv::VideoCapture _cap = cv::VideoCapture();
};
