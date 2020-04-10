/* Copyright (c) 2020 Andrei Gramakov. All rights reserved.
 *
 * This file is licensed under the terms of the MIT license.
 * For a copy, see: https://opensource.org/licenses/MIT
 *
 * site:    https://agramakov.me
 * e-mail:  mail@agramakov.me
 */

#pragma once

#include "I2cWithRegs.h"

#define REG_CMD 0
#define REG_MODE 1
extern I2cWithRegs i2c;
void i2c_init(void);
void i2c_reqEv();
void i2c_rcvEv(int howMany);