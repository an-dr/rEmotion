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
#include "i2c.h"
#include "display.h"


Connection_t connection[5] = {
    {.cmd_code = CMD_CALM, .func = display_calm},
    {.cmd_code = CMD_BLINK, .func = display_blink},
    {.cmd_code = CMD_ANGRY, .func = display_angry},
    {.cmd_code = CMD_HAPPY, .func = display_happy},
    {.cmd_code = CMD_SAD, .func = display_sad},
};

ControlCallbacks Cc;

void control_poll() {
    int new_cmd = i2c.Get(REG_CMD);
    if ((new_cmd != CMD_NONE&0xFF) & (new_cmd != CMD_DONE)) {
        i2c.Set(REG_MODE, new_cmd); // exec the cmd
        Cc.Exec(new_cmd);
        i2c.Set(REG_CMD, CMD_DONE); // set that is done
    }
}

