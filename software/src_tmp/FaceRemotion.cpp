// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <string>
#include <CppLinuxSerial/SerialPort.hpp>
#include <unistd.h>

#include "FaceRemotion.hpp"

#define CMD_CALM 0x30
#define CMD_BLINK 0x31
#define CMD_ANGRY 0x32
#define CMD_HAPPY 0x33
#define CMD_SAD 0x34
#define CMD_DUNNO 0x35
#define CMD_CONFUSED 0x36
#define CMD_THINKING 0x37

using namespace mn::CppLinuxSerial;

FaceRemotion::FaceRemotion(std::string port_name, int baudrate)
    : serialPort(port_name, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE,
                 NumStopBits::ONE) {
    serialPort.SetTimeout(100);  // Block for up to 100ms to receive data
    serialPort.Open();
}

void FaceRemotion::ShowThinking() { serialPort.Write("7"); }

void FaceRemotion::ShowBlink(int delay) {
    // write(m_serial_port, "0", 1);
    serialPort.Write("1");
    Delay(delay);
    serialPort.Write("0");
}

void FaceRemotion::ShowCalm(int delay) {
    serialPort.Write("0");
    Delay(delay);
}

void FaceRemotion::ShowHappy(int delay) {
    serialPort.Write("3");
    Delay(1000);
}

void FaceRemotion::ShowSad(int delay) {
    serialPort.Write("4");
    Delay(1000);
}

void FaceRemotion::ShowDunno(int delay) {
    serialPort.Write("5");
    Delay(delay);
}

void FaceRemotion::ShowConfused(int delay) {
    serialPort.Write("6");
    Delay(1000);
}

void FaceRemotion::Delay(int ms) { usleep(ms * 1000); }

FaceRemotion::~FaceRemotion() { serialPort.Close(); }
