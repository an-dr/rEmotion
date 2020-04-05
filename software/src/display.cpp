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


const unsigned char zk_calm2_bits[] PROGMEM = ZK_CALM;
const unsigned char zk_blink_bits[] PROGMEM = ZK_BLINK;


void display_init(void) {
#if KS0108_128X64
    /* U8g2 Project: KS0108 Test Board */
    pinMode(LCD_RW, OUTPUT);
    digitalWrite(LCD_RW, 0);
#endif
    u8g2.begin();
}


void blinking(void)
{
    u8g2.firstPage();
    do {
        u8g2.drawXBMP(0, 0, FACE_WIDTH, FACE_HEIGHT, zk_calm2_bits);
    } while (u8g2.nextPage());
    _delay_ms(2000);
    do {
        u8g2.drawXBMP(0, 0, FACE_WIDTH, FACE_HEIGHT, zk_blink_bits);
    } while (u8g2.nextPage());
    _delay_ms(100);
}
