// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "RemotionController.hpp"

using namespace Re;
using namespace mn::CppLinuxSerial;

RemotionController::RemotionController(const std::string &port_name)
    : port_name(port_name) {
    serial = new SerialPort(port_name, BaudRate::B_9600);
    serial->SetParity(Parity::NONE);
    serial->SetNumStopBits(NumStopBits::ONE);
    serial->SetNumDataBits(NumDataBits::EIGHT);
    serial->SetTimeout(SERIAL_PORT_TIMEOUT);
    serial->Open();
}

RemotionController::~RemotionController() {
    serial->Close();
    delete serial;
}

RemotionError RemotionController::setExpression(RemotionExpression exp) {
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
    return RemotionError::NO_ERROR;
}
