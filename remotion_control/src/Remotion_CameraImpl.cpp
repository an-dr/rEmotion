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

#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"
#include "V4l2Capture.h"

#include "Remotion.hpp"

RemotionError Remotion::readVideoFrame(char *out_buffer,
                                       size_t out_buffer_size) {
    if (_videoCapture == nullptr) {
        _videoCapture = _createVideoCapture(
            _videoCaptureParams.device, _videoCaptureParams.v4l2_pix_fmt,
            _videoCaptureParams.width, _videoCaptureParams.height,
            _videoCaptureParams.fps);
        if (_videoCapture == nullptr) {
            return RemotionError::ERROR;
        }
    }

    timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    // If the camera is not opened, return an error
    if (!_videoCapture->isReadable(&tv)) {
        return RemotionError::ERROR_READ_PORT;
    }

    // Read the frame from the camera
    int rsize = _videoCapture->read(out_buffer, out_buffer_size);
    if (rsize == -1) {
        return RemotionError::ERROR_READ_IMAGE;
    }

    return RemotionError::NO_ERROR;
}

V4l2Capture *Remotion::_createVideoCapture(std::string &device,
                                           unsigned int format, int width,
                                           int height, int fps) {
    V4L2DeviceParameters param(device.c_str(), format, width, height, fps);
    auto new_obj = V4l2Capture::create(param);
    return new_obj;
}

V4l2Capture *Remotion::_getVideo() {
    if (_videoCapture == nullptr) {
        _videoCapture = _createVideoCapture(
            _videoCaptureParams.device, _videoCaptureParams.v4l2_pix_fmt,
            _videoCaptureParams.width, _videoCaptureParams.height,
            _videoCaptureParams.fps);
    }
    return _videoCapture;
}

int Remotion::getVideoCaptureBufferSize(std::string &device,
                                        unsigned int format, int width,
                                        int height, int fps) {
    auto v = _createVideoCapture(device, format, width, height, fps);
    if (v == nullptr) {
        return -1;
    } else {
        auto sz = v->getBufferSize();
        delete v;
        return sz;
    }
}
