#include<stdio.h>
#include<stdlib.h>
#include "LoadPNG.h"
#define MAX_SIZE (16 * 1024 * 1024) // maximum image size 16 mb


int readPng() {
    char *buffer = malloc(MAX_SIZE);  // input buffer for image in chars

    if (!buffer) {
        fprintf(stderr, "Couldn't allocate memory\n");
        return 1;
    }

    FILE *f = fopen("../testImage.png", "r+"); // opening file

    if (!f) {   // checking and reporting possible file open errors
        perror("fopen");
        free(buffer);
        return 1;
    }
    printf("%x\n", buffer[0]);
    checkHeader(buffer);

    // taking the header, saving it to buffer
    unsigned long size = fread(buffer, 1, MAX_SIZE, f);

//    for (int i = 0; i < 8; i++) {
//        printf("%x\n", buffer[i]);
//    }

    printf("%lu\n", size);
    printf("%s\n", buffer);

    fclose(f);
    free(buffer);

    return 0;
}

void validate(int val, const char *msg) {
    if(!val) {
        fprintf(stderr, "Invalid file: %s\n", msg);
        exit(1);
    }
}

void checkHeader(const char *buf) {
    validate(buf[0] == '\x89', "header byte 1");
    validate((unsigned char)buf[1] == 0x50, "header byte 2");               //letter P
    validate((unsigned char)buf[2] == 0x4E, "header byte 3");               //letter N
    validate((unsigned char)buf[3] == 0x47, "header byte 4");               //letter G
    validate((unsigned char)buf[4] == 0x0D, "header byte 5");
    validate((unsigned char)buf[5] == 0x0A, "header byte 6");
    validate((unsigned char)buf[6] == 0x1A, "header byte 7");
    validate((unsigned char)buf[7] == 0x0A, "header byte 8");
}