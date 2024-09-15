// *************************************************************************
//
// Copyright (c) 2020 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "controlcallback.h"
#include "common_config.h"
#include "display.h"
#include "stepper.hpp"


Connection_t connection[10] = {
    {.cmd_code = CMD_TARGET_FACE | CMD_CALM, .func = display_calm},
    {.cmd_code = CMD_TARGET_FACE | CMD_BLINK, .func = display_blink},
    {.cmd_code = CMD_TARGET_FACE | CMD_ANGRY, .func = display_angry},
    {.cmd_code = CMD_TARGET_FACE | CMD_HAPPY, .func = display_happy},
    {.cmd_code = CMD_TARGET_FACE | CMD_SAD, .func = display_sad},
    {.cmd_code = CMD_TARGET_FACE | CMD_DUNNO, .func = display_dunno},
    {.cmd_code = CMD_TARGET_FACE | CMD_CONFUSED, .func = display_confused},
    {.cmd_code = CMD_TARGET_FACE | CMD_THINKING, .func = display_thinking},
    {.cmd_code = CMD_LEFT, .func = stepper_left},
    {.cmd_code = CMD_RIGHT, .func = stepper_right}
};

ControlCallbacks Cc;

int cmd;

void control_poll( void * arg) {
    int new_cmd = cmd;
    cmd = CMD_NONE;
    if ((new_cmd != CMD_NONE&0xFF) & (new_cmd != CMD_DONE)) {
        Cc.Exec(new_cmd);
    }
}

