#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

int main(int argc, char *argv[]) {

    // Load the PNG image
    unsigned error;
    unsigned char *image;
    unsigned width, height;
    char *filePath = "../inputImage/testImage.png";

    error = lodepng_decode32_file(&image, &width, &height, filePath);
    if (error) {
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        return 1;
    }

    // Convert the image to grayscale
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            unsigned char *pixel = image + (y * width + x) * 4;
            unsigned char gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
            pixel[0] = gray;
            pixel[1] = gray;
            pixel[2] = gray;
        }
    }

    // Save the grayscale image
    error = lodepng_encode32_file("../outputImage/output.png", image, width, height);
    if (error) {
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        return 1;
    }

    // Clean up
    free(image);
    return 0;
}

