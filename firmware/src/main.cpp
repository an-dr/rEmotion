#include <Arduino.h>
#include "controlcallback.h"
#include "display.h"
#include "pinout.h"
#include "serial.h"
#include "ulog.h"
#include "stepper.hpp"



void ulog_callback(ulog_Event *ev, void *arg) {
    char buffer[128];
    ulog_event_to_cstr(ev, buffer, sizeof(buffer));
    Serial.println(buffer);
}

void ulog_prefix(ulog_Event *ev, char *prefix, size_t prefix_size) {
    long ms = millis();
    snprintf(prefix, prefix_size, "%lu ms", ms);
}

void setup() {
    serial_init();
    ulog_enable_all_topics();
    ulog_add_callback(ulog_callback, NULL, LOG_TRACE);
    ulog_set_prefix_fn(ulog_prefix);
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
