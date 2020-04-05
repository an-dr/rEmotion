#include <Arduino.h>
#include "pinout.h"
#include "display.h"
#include "i2c.h"


void setup(void) {
    display_init();
    i2c_init();
}

void loop(void) {
    blinking();
}