// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <Arduino.h>
#include <Stepper.h>
#include <FreeRTOS.h>
#include <task.h>
#include "stepper.hpp"
#include "ulog.h"

Stepper stepper(2048, 9, 11, 12, 10);
static int stepper_pos = 0;
constexpr int STEPPER_MOVE = 100;

void stepper_init()
{
    stepper.setSpeed(5);
}

void stepper_left()
{
    stepper_pos = -STEPPER_MOVE;
}

void stepper_right()
{
    stepper_pos = STEPPER_MOVE;
}

void stepper_once()
{
    if (stepper_pos != 0)
    {
        stepper.step(stepper_pos);
    }
    stepper_pos = 0;
    
}
