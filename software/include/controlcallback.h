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

#include "ControlCallbacks.h"

#define SIZE_ARR(x) (sizeof(x) / sizeof(x[0]))

extern int cmd;
extern ControlCallbacks Cc;
void control_poll();