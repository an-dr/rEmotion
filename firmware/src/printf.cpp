#include "printf.h"


int getChar(FILE *fp) {
    while (!(Serial.available()))
        ;
    return (Serial.read());
}

int putChar(char c, FILE *fp) {
    if (c == '\n') {
        putChar((char)'\r', fp);
    }
    Serial.write(c);
    return 0;
}

void printf_init(void)
{
    fdevopen(putChar, getChar);
    // printf("[printf] Ready!\n");
}