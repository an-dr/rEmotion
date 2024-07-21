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
        auto err = _createVideoCapture(
            _videoCaptureParams.device, _videoCaptureParams.v4l2_pix_fmt,
            _videoCaptureParams.width, _videoCaptureParams.height,
            _videoCaptureParams.fps);
        if (err != RemotionError::NO_ERROR) {
            return err;
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

RemotionError Remotion::_createVideoCapture(std::string &device,
                                            unsigned int format, int width,
                                            int height, int fps) {
    V4L2DeviceParameters param(device.c_str(), format, width, height, fps);
    _videoCapture = V4l2Capture::create(param);
    if (_videoCapture == NULL) {
        return RemotionError::ERROR_OPEN_PORT;
    }
    return RemotionError::NO_ERROR;
}

V4l2Capture *Remotion::_getVideo() {
    if (_videoCapture == nullptr) {
        auto err = _createVideoCapture(
            _videoCaptureParams.device, _videoCaptureParams.v4l2_pix_fmt,
            _videoCaptureParams.width, _videoCaptureParams.height,
            _videoCaptureParams.fps);
        if (err != RemotionError::NO_ERROR) {
            return nullptr;
        }
    }
    return _videoCapture;
}

int Remotion::getVideoCaptureBufferSize() {
    auto v = _getVideo();
    if (v == nullptr) {
        return -1;
    } else {
        return v->getBufferSize();
    }
}
