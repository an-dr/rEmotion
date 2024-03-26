/* Copyright (c) 2020 Andrei Gramakov. All rights reserved.
 *
 * This file is licensed under the terms of the MIT license.
 * For a copy, see: https://opensource.org/licenses/MIT
 *
 * site:    https://agramakov.me
 * e-mail:  mail@agramakov.me
 */

#pragma once

#include <Arduino.h>

#include "pinout.h"
#include "unifaces.h"
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#if SH1106_128X64
extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;
#endif
#if KS0108_128X64
extern U8G2_KS0108_128X64_F u8g2;
#endif

void display_init(void);
void display_sad();
void display_happy();
void display_angry();
void display_blink();
void display_calm();
void display_dunno();
void display_confused();
void display_thinking();
void greeting(void);
void blinking(void);
void demo(void);

