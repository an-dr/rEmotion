#include "printf.h"


int getChar(FILE *fp) {
    while (!(Serial.available()))
        ;
    return (Serial.read());
}


// int __io_putchar(int ch)
// {
//     Serial.write(ch);
//     return ch;
// }

// int _write(int file, char *ptr, int len)
// {
//     int DataIdx;
//     for (DataIdx = 0; DataIdx < len; DataIdx++) { __io_putchar(*ptr++); }
//     return len;
// }
// int putChar(char c, FILE *fp) {
//     if (c == '\n') {
//         putChar((char)'\r', fp);
//     }
//     Serial.write(c);
//     return 0;
// }

// FILE my_stdout = {0};
// FILE my_stdin = {0};

// void printf_init(void)
// {
//     my_stdout._file = putChar;
//     my_stdin._file = getChar;
    
    
//     stdout = &my_stdout;
//     stdin = &my_stdin;
//     // printf("[printf] Ready!\n");
// }
