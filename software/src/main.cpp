#include <Arduino.h>
#include <U8g2lib.h>
#include "zakhar_faces.h"
#include "pinout.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


#if SH1106_128X64
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#endif

#if KS0108_128X64
U8G2_KS0108_128X64_F u8g2(U8G2_R2,  LCD_D0, LCD_D1, LCD_D2, LCD_D3,
                                    LCD_D4, LCD_D5, LCD_D6, LCD_D7,
                                    /*enable=*/LCD_E, /*dc=*/LCD_DC,
                                    /*cs0=*/LCD_CS0, /*cs1=*/LCD_CS1,
                                    /*cs2=*/U8X8_PIN_NONE, /* reset=*/LCD_RESET); // Set R/W to low!
#endif
// End of constructor list

void setup(void) {

#if KS0108_128X64
    /* U8g2 Project: KS0108 Test Board */
    pinMode(LCD_RW, OUTPUT);
    digitalWrite(LCD_RW, 0);
#endif
    u8g2.begin();
}



static const unsigned char zk_calm2_bits[] PROGMEM = ZK_CALM;
static const unsigned char zk_blink_bits[] PROGMEM = ZK_BLINK;

uint8_t m = 30;
// extern unsigned char zk_calm_bits[];
void loop(void) {
    u8g2.firstPage();

    do {
        u8g2.drawXBMP(0, 0, FACE_WIDTH, FACE_HEIGHT, zk_calm2_bits);
    } while (u8g2.nextPage());
    _delay_ms(2000);

    // u8g2.clearDisplay();
    do {
        u8g2.drawXBMP(0, 0, FACE_WIDTH, FACE_HEIGHT, zk_blink_bits);
    } while (u8g2.nextPage());
    _delay_ms(100);

    // u8g2.clearDisplay();
    // _delay_ms(300);/*  */
}