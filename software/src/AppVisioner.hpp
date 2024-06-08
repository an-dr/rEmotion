// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "App.hpp"

class AppVisioner : public App {
 public:
    AppVisioner(FaceInterface *face, InputInterface *input,
                InterfaceSceneReader *scene_input);
    void Delay(int ms) override;
    ~AppVisioner() = default;
};
