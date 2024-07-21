// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <string>
#include <unistd.h>

#include "CppLinuxSerial/SerialPort.hpp"
#include "RemotionError.hpp"
#include "RemotionExpression.hpp"
#include "RemotionStatus.hpp"

#include "Remotion.hpp"

mn::CppLinuxSerial::SerialPort *Remotion::_getSerialPort() {
    if (_serialPort == nullptr) {
        _serialPort = new mn::CppLinuxSerial::SerialPort();
        _serialPort->SetDevice(_port_name);
        _serialPort->SetBaudRate(mn::CppLinuxSerial::BaudRate::B_9600);
        _serialPort->SetParity(mn::CppLinuxSerial::Parity::NONE);
        _serialPort->SetNumStopBits(mn::CppLinuxSerial::NumStopBits::ONE);
        _serialPort->SetNumDataBits(mn::CppLinuxSerial::NumDataBits::EIGHT);
        _serialPort->SetTimeout(SERIAL_PORT_TIMEOUT);
        _serialPort->Open();
        sleep(
            SERIAL_PORT_INIT_ANIMATION_DURATION_S);  // sleep for initialization
                                                     // animation
    }
    return _serialPort;
}

RemotionError Remotion::setExpression(RemotionExpression exp) {
    auto serial = _getSerialPort();
    switch (exp) {
    case RemotionExpression::CALM:
        serial->Write("0");
        break;
    case RemotionExpression::BLINK:
        serial->Write("1");
        break;
    case RemotionExpression::ANGRY:
        serial->Write("2");
        break;
    case RemotionExpression::HAPPY:
        serial->Write("3");
        break;
    case RemotionExpression::SAD:
        serial->Write("4");
        break;
    case RemotionExpression::DUNNO:
        serial->Write("5");
        break;
    case RemotionExpression::CONFUSED:
        serial->Write("6");
        break;
    case RemotionExpression::THINKING:
        serial->Write("7");
        break;
    default:
        break;
    }
    return RemotionError();
}
