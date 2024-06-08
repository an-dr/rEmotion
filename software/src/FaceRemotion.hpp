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

#include "FaceInterface.hpp"

class FaceRemotion : public FaceInterface {
 public:
    FaceRemotion(std::string port_name, int baudrate);
    void ShowThinking() override;
    void ShowBlink(int delay = 500) override;
    void ShowCalm(int delay = 500) override;
    void ShowHappy(int delay = 500) override;
    void ShowSad(int delay = 500) override;
    void ShowDunno(int delay = 500) override;
    void ShowConfused(int delay = 500) override;
    void Delay(int ms) override;
    ~FaceRemotion();

 private:
    mn::CppLinuxSerial::SerialPort serialPort;
};
