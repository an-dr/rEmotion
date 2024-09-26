// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <cstdio>
#include <stdexcept>
#include <string>

#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"
#include "V4l2Capture.h"

#include "RemotionCamera.hpp"

using namespace Re;

RemotionCamera::RemotionCamera(const std::string &video_device,
                               unsigned int v4l2_pix_fmt, int width, int height,
                               int fps) {
    videoCaptureParams = new V4L2DeviceParameters(
        video_device.c_str(), v4l2_pix_fmt, width, height, fps);
    videoCapture = V4l2Capture::create(*videoCaptureParams);
    if (videoCapture == nullptr) {
        throw std::runtime_error("Failed to init " + video_device +
                                 ". Is the camera connected?");
    }
}

RemotionCamera::~RemotionCamera() {
    if (videoCapture != nullptr) {
        delete videoCapture;
    }
}

int RemotionCamera::getVideoCaptureBufferSize() {
    if (videoCapture == nullptr) {
        return -1;
    }
    return videoCapture->getBufferSize();
}

RemotionError RemotionCamera::readVideoFrame(char *out_buffer,
                                             size_t out_buffer_size) {
    if (videoCapture == nullptr) {
        return RemotionError::ERROR_OPEN_PORT;
    }

    timeval tv{1, 0};  // 1 second, 0 microseconds

    // If the camera is not opened, return an error
    if (!videoCapture->isReadable(&tv)) {
        return RemotionError::ERROR_READ_PORT;
    }

    // Read the frame from the camera
    int rsize = videoCapture->read(out_buffer, out_buffer_size);
    if (rsize == -1) {
        return RemotionError::ERROR_READ_IMAGE;
    }

    return RemotionError::NO_ERROR;
}
