#include <Arduino.h>

#include "pinout.h"
#include "display.h"
#include "i2c.h"
#include "serial.h"
#include "ulog.h"
#include "controlcallback.h"



// Custom putchar function to redirect printf output to Serial
extern "C" int putchar(int ch) {
    Serial.write(ch); // Send the character to Serial
    return ch;        // Return the character
}


void ulog_callback(ulog_Event *ev, void *arg) {
    static char buffer[128];
    ulog_event_to_cstr(ev, buffer, sizeof(buffer));
    ((SerialUSB *) arg)->println(buffer);
}


void setup() {
    ulog_add_callback(ulog_callback, (void* )&Serial, LOG_TRACE);
    Serial.begin(9600); // Initialize serial communication at 9600 baud
    display_init();
    // i2c.Init(0x2c, 16, (void *)i2c_reqEv, (void *)i2c_rcvEv);
    // Cc.Init(connection,SIZE_ARR(connection));

    // greeting();
}

void loop() {
    static int a=0;
    // Your main code here
    log_info("Hello from Arduino's loop() %d!", a++); // Example usage of printf
    // blinking();
    // demo();
    // blinking();
    // control_poll();
    // i2c.Print();
    delay(1000); // Delay for 1 second
}
