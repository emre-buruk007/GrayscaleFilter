#include<stdio.h>
#include<stdlib.h>
#include "LoadPNG.h"
#define MAX_SIZE (16 * 1024 * 1024) // maximum image size 16 mb


int readPng() {
    unsigned char *buffer = malloc(MAX_SIZE);  // input buffer for image in chars

    // memory allocation error checking
    if (!buffer) {
        fprintf(stderr, "Couldn't allocate memory\n");
        return 1;
    }

    FILE *f = fopen("../testImage.png", "r"); // opening file

    // checking and reporting possible file open errors
    if (!f) {
        perror("fopen");
        free(buffer);
        return 1;
    }


    // taking the header, saving it to buffer
    unsigned long size = fread(buffer, 1, MAX_SIZE, f);

    // checking to see if the file is a PNG
    checkHeader(buffer);

    // below are debug codes
//    for (int i = 0; i < 8; i++) {
//        printf("%02X ", buffer[i]);
//    }
//    printf("\n");
//    for (int i = 0; i < 8; i++) {
//        printf("%c ", buffer[i]);
//    }
//
//    printf("\n%lu\n", size);
//    printf("%s\n", buffer);

    fclose(f);
    free(buffer);

    return 0;
}

void validate(int val, const char *msg) {
    if(!val) {
        fprintf(stderr, "Invalid file: %s\n", msg);
        perror("");
        exit(1);
    }
}

void checkHeader(const char *buf) {
    validate((unsigned char)buf[0] == 0x89, "header byte 1");
    validate((unsigned char)buf[1] == 0x50, "header byte 2");               //letter P
    validate((unsigned char)buf[2] == 0x4E, "header byte 3");               //letter N
    validate((unsigned char)buf[3] == 0x47, "header byte 4");               //letter G
    validate((unsigned char)buf[4] == 0x0D, "header byte 5");
    validate((unsigned char)buf[5] == 0x0A, "header byte 6");
    validate((unsigned char)buf[6] == 0x1A, "header byte 7");
    validate((unsigned char)buf[7] == 0x0A, "header byte 8");
}