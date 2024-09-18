#include "display.h"
#include "ulog.h"

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, 
                                /* clock=*/ LCD_E, 
                                /* data=*/ LCD_RW, 
                                /* CS=*/ LCD_DC);

const uint8_t face_calm[] PROGMEM = UNIFACE_CALM;
const uint8_t face_blink[] PROGMEM = UNIFACE_BLINK;
const uint8_t face_angry[] PROGMEM = UNIFACE_ANGRY;
const uint8_t face_happy[] PROGMEM = UNIFACE_HAPPY;
const uint8_t face_sad[] PROGMEM = UNIFACE_SAD;
const uint8_t face_dunno[] PROGMEM = UNIFACE_DUNNO;
const uint8_t face_confused[] PROGMEM = UNIFACE_CONFUSED;
const uint8_t face_thinking1[] PROGMEM = UNIFACE_THINKING1;
const uint8_t face_thinking2[] PROGMEM = UNIFACE_THINKING2;
const uint8_t face_thinking3[] PROGMEM = UNIFACE_THINKING3;

void display_init(void) {
    logt_info("Display", "init");
    u8g2.begin();

    display_blink();
    logt_info("Display", "init done");
}

static void set_face(const uint8_t *face) {
    u8g2.firstPage();
    do {
        u8g2.drawXBMP(0, 0, UNIFACE_WIDTH, UNIFACE_HEIGHT, face);
    } while (u8g2.nextPage());
}

void display_calm() {
    logt_debug("Display", "calm face");
    set_face(face_calm);
}

void display_blink() {
    logt_debug("Display", "blink face");
    set_face(face_blink);
}
void display_angry() {
    logt_debug("Display", "angry face");
    set_face(face_angry);
}
void display_happy() {
    logt_debug("Display", "happy face");
    set_face(face_happy);
}
void display_sad() {
    logt_debug("Display", "sad face");
    set_face(face_sad);
}

void display_dunno() {
    logt_debug("Display", "dunno face");
    set_face(face_dunno);
}

void display_confused() {
    logt_debug("Display", "confused face");
    set_face(face_confused);
}

void demo(void)
{
    display_calm();
    delay(2000);
    display_blink();
    delay(100);
    display_calm();
    delay(1000);

    display_angry();
    delay(2000);

    display_calm();
    delay(2000);
    display_blink();
    delay(100);
    display_calm();
    delay(1000);

    display_sad();
    delay(2000);

    display_calm();
    delay(2000);
    display_blink();
    delay(100);
    display_calm();
    delay(1000);

    display_happy();
    delay(2000);

    display_calm();
    delay(2000);
    display_blink();
    delay(100);
    display_calm();
    delay(1000);


}

void blinking(void) {
    set_face(face_calm);
    delay(3000);
    set_face(face_blink);
    delay(10);
}


void greeting(void) {
    set_face(face_thinking1);
    delay(100);
    set_face(face_thinking2);
    delay(100);
    set_face(face_thinking3);
    delay(100);
    set_face(face_blink);
    delay(300);
    set_face(face_calm);
    delay(700);
    set_face(face_happy);
    delay(1000);
    set_face(face_calm);
}
