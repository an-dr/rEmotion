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

#include "CppLinuxSerial/SerialPort.hpp"
#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"
#include "V4l2Capture.h"

struct VideoCaptureParams {
    std::string device;
    unsigned int v4l2_pix_fmt;
    int width;
    int height;
    int fps;
};

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
    const RemotionStatus start(const std::string &port_name,
                               const std::string &video_device,
                               unsigned int v4l2_pix_fmt, int width, int height,
                               int fps);

    /// @brief Stop Remotion camera
    void stop();

    /// @brief Read video frame
    /// @param out_buffer - output buffer
    /// @param out_buffer_size - output buffer size
    /// @return RemotionError
    RemotionError readVideoFrame(char *out_buffer, size_t out_buffer_size);

    /// @brief Set expression
    /// @param exp - expression
    /// @return RemotionError
    RemotionError setExpression(RemotionExpression exp);

    /// @brief Get status
    /// @return RemotionStatus
    [[nodiscard]] RemotionStatus getStatus() const;

    int getVideoCaptureBufferSize();

 private:
    RemotionError _createVideoCapture(std::string &device, unsigned int format,
                                      int width, int height, int fps);

    V4l2Capture *_getVideo();
    mn::CppLinuxSerial::SerialPort *_getSerialPort();

    constexpr static int SERIAL_PORT_TIMEOUT = 100;

    mn::CppLinuxSerial::SerialPort *_serialPort = nullptr;
    RemotionStatus _status = RemotionStatus();
    std::string _port_name = "";
    VideoCaptureParams _videoCaptureParams = {};
    V4l2Capture *_videoCapture = nullptr;
};
