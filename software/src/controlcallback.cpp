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
// #include "common_config.h"

#define NO_CMD (-1)
default

int cmd;

static Connection_t connection[5] = {
    // {.cmd_code = CMD_FORWARD, .func = W},
    // {.cmd_code = CMD_BACKWARD, .func = S},
    // {.cmd_code = CMD_LEFT, .func = A},
    // {.cmd_code = CMD_RIGHT, .func = D},
    // {.cmd_code = CMD_STOP, .func = Stop},
};

ControlCallbacks Cc(connection, SIZE_ARR(connection));

void control_poll() {
    if (cmd != NO_CMD) {
        Cc.Exec(cmd);
        cmd = NO_CMD;
    }
}

