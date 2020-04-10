#include "display.h"

#if SH1106_128X64
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
#endif

#if KS0108_128X64
U8G2_KS0108_128X64_F u8g2(U8G2_R2, LCD_D0, LCD_D1, LCD_D2, LCD_D3,
                          LCD_D4, LCD_D5, LCD_D6, LCD_D7,
                          /*enable=*/LCD_E, /*dc=*/LCD_DC,
                          /*cs0=*/LCD_CS0, /*cs1=*/LCD_CS1,
                          /*cs2=*/U8X8_PIN_NONE, /* reset=*/LCD_RESET); // Set R/W to low!
#endif

const uint8_t zk_calm[] PROGMEM = ZK_CALM;
const uint8_t zk_blink[] PROGMEM = ZK_BLINK;
const uint8_t zk_angry[] PROGMEM = ZK_ANGRY;
const uint8_t zk_happy[] PROGMEM = ZK_HAPPY;
const uint8_t zk_sad[] PROGMEM = ZK_SAD;

void display_init(void) {
#if KS0108_128X64
    /* U8g2 Project: KS0108 Test Board */
    pinMode(LCD_RW, OUTPUT);
    digitalWrite(LCD_RW, 0);
#endif
    u8g2.begin();
}

static void set_face(const uint8_t *face) {
    u8g2.firstPage();
    do {
        u8g2.drawXBMP(0, 0, FACE_WIDTH, FACE_HEIGHT, face);
    } while (u8g2.nextPage());
}

void display_calm() {
    set_face(zk_calm);
}

void display_blink() {
    set_face(zk_blink);
}
void display_angry() {
    set_face(zk_angry);
}
void display_happy() {
    set_face(zk_happy);
}
void display_sad() {
    set_face(zk_sad);
}


void demo(void)
{
    display_calm();
    _delay_ms(2000);
    display_blink();
    _delay_ms(100);
    display_calm();
    _delay_ms(1000);

    display_angry();
    _delay_ms(2000);

    display_calm();
    _delay_ms(2000);
    display_blink();
    _delay_ms(100);
    display_calm();
    _delay_ms(1000);

    display_sad();
    _delay_ms(2000);

    display_calm();
    _delay_ms(2000);
    display_blink();
    _delay_ms(100);
    display_calm();
    _delay_ms(1000);

    display_happy();
    _delay_ms(2000);

    display_calm();
    _delay_ms(2000);
    display_blink();
    _delay_ms(100);
    display_calm();
    _delay_ms(1000);


}

void blinking(void) {
    set_face(zk_calm);
    _delay_ms(2000);
    set_face(zk_blink);
    _delay_ms(300);
}
