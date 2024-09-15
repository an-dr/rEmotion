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

extern U8G2_ST7920_128X64_1_SW_SPI u8g2;

void display_init(void);
void display_sad();
void display_happy();
void display_angry();
void display_blink();
void display_calm();
void display_dunno();
void display_confused();
void greeting(void);
void blinking(void);
void demo(void);

