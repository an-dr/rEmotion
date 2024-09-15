#include <Arduino.h>
#include "controlcallback.h"
#include "display.h"
#include "pinout.h"
#include "serial.h"
#include "ulog.h"
#include "stepper.hpp"



void ulog_callback(ulog_Event *ev, void *arg) {
    static char buffer[128];
    ulog_event_to_cstr(ev, buffer, sizeof(buffer));
    ((SerialUSB *) arg)->println(buffer);
}


void setup() {
    ulog_add_callback(ulog_callback, (void* )&Serial, LOG_TRACE);
    serial_init();
    display_init();
    Cc.Init(connection,9);
    greeting();
}

void setup1() {
    stepper_init();
}

void loop() {
    serial_poll(NULL);
    control_poll(NULL);
    
}

void loop1() {
    stepper_once();
}
