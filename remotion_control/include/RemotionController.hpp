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

namespace Re {

class RemotionController {
 private:
    constexpr static int SERIAL_PORT_TIMEOUT = 100;
    constexpr static int SERIAL_PORT_INIT_ANIMATION_DURATION_S = 10;
    mn::CppLinuxSerial::SerialPort *serial = nullptr;
    std::string port_name = "";

 public:
    RemotionController(const std::string &port_name);
    RemotionController(RemotionController &&) = delete;
    RemotionController(const RemotionController &) = delete;
    RemotionController &operator=(const RemotionController &) = delete;
    RemotionController &operator=(RemotionController &&) = delete;
    ~RemotionController();

    /// @brief Set expression
    /// @param exp - expression
    /// @return RemotionError
    RemotionError setExpression(RemotionExpression exp);
};

};  // namespace Remotion
