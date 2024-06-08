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

RemotionError Remotion::start(std::string port_name, int video_source)
{
    return RemotionError();
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

RemotionStatus Remotion::getStatus()
{
    return RemotionStatus();
}
