// Copyright (c) 2024 Andrei Gramakov. All rights reserved.

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        printf("Hello, %s!\n", argv[1]);
    } else {
    printf("Hello!\n");
    }
    return 0;
}
