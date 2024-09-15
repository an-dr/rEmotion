#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
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


static void serial_thread(void *pvParameters) {
    while (1) {
        serial_poll(NULL);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

static void control_thread(void *pvParameters) {
    while (1) {
        control_poll(NULL);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}



static void stepper_thread(void *pvParameters) {
    while (1) {
        // stepper.step(100);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // stepper.step(-100);
        stepper_once();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup() {
    ulog_add_callback(ulog_callback, (void* )&Serial, LOG_TRACE);
    serial_init();
    display_init();
    stepper_init();
    Cc.Init(connection,SIZE_ARR(connection));

    greeting();
    
    log_info("Hello from Arduino"); // Example usage of printf
    
    xTaskCreate(serial_thread, "Serial", 1000, NULL, 1, NULL);
    xTaskCreate(control_thread, "Control", 1000, NULL, 1, NULL);
}

void setup1() {
    xTaskCreate(stepper_thread, "Stepper", 1000, NULL, 1, NULL);
}

void loop() {
    // new thread
}
