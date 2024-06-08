// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "AppVisioner.hpp"
#include <opencv2/highgui.hpp>
#include "FaceInterface.hpp"
#include "InputInterface.hpp"

AppVisioner::AppVisioner(FaceInterface *face, InputInterface *input,
                         InterfaceSceneReader *scene_input)
    : App(face, input, scene_input) {}

void AppVisioner::Delay(int ms) { cv::waitKey(ms); }
