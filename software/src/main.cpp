#include <Arduino.h>
#include "pinout.h"
#include "display.h"
#include "i2c.h"
#include "serial.h"
#include "printf.h"
#include "controlcallback.h"


void setup(void) {
    printf_init();
    display_init();
    i2c.Init(0x2c, 16, (void *)i2c_reqEv, (void *)i2c_rcvEv);
    Cc.Init(connection,SIZE_ARR(connection));
    serial_init();

    greeting();
}

void loop(void) {
    // blinking();
    // demo();
    blinking();
    serial_poll();
    control_poll();
    i2c.Print();
}
