#include <Arduino.h>
#include <LibPrintf.h>

#include "pinout.h"
#include "display.h"
#include "i2c.h"
#include "serial.h"
#include "controlcallback.h"


void setup(void) {
    delay(3000);
    serial_init();
    printf("Setup\n");
    // display_init();
    // i2c.Init(0x2c, 16, (void *)i2c_reqEv, (void *)i2c_rcvEv);
    // Cc.Init(connection,SIZE_ARR(connection));

    // greeting();
}

void loop(void) {
    // blinking();
    // demo();
    // blinking();
    printf("loop\n");
    delay(3000);
    // control_poll();
    // i2c.Print();
}
