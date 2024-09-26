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

#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"
#include "V4l2Capture.h"

namespace Re {

class RemotionCamera {

 public:
    RemotionCamera(const std::string &video_device, unsigned int v4l2_pix_fmt,
                   int width, int height, int fps);
    RemotionCamera(RemotionCamera &&) = delete;
    RemotionCamera(const RemotionCamera &) = delete;
    RemotionCamera &operator=(const RemotionCamera &) = delete;
    RemotionCamera &operator=(RemotionCamera &&) = delete;
    ~RemotionCamera();

    /// @brief Read video frame
    /// @param out_buffer - output buffer
    /// @param out_buffer_size - output buffer size
    /// @return RemotionError
    RemotionError readVideoFrame(char *out_buffer, size_t out_buffer_size);

    /// @brief Get video capture buffer size for storing a frame based on
    /// provided parameters
    int getVideoCaptureBufferSize();

 private:
    V4L2DeviceParameters *videoCaptureParams = nullptr;
    V4l2Capture *videoCapture = nullptr;
};

};  // namespace Re
