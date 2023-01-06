#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Open the input file
    FILE *fp = fopen("../inputImage/testImage.png", "rb");
    if (!fp) {
        printf("Error: Unable to open input file\n");
        return 1;
    }

    // Read the file into a buffer
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);
    unsigned char *buffer = (unsigned char*)malloc(size);
    fread(buffer, 1, size, fp);

    // Close the input file
    fclose(fp);

    // Check that the file is a PNG image
    if (size < 8 || buffer[0] != 137 || buffer[1] != 80 || buffer[2] != 78 || buffer[3] != 71 || buffer[4] != 13 || buffer[5] != 10 || buffer[6] != 26 || buffer[7] != 10) {
        printf("Error: Input file is not a valid PNG image\n");
        return 1;
    }

    // Parse the PNG header to get the width and height
    unsigned width, height;
    if (buffer[12] == 'I' && buffer[13] == 'H' && buffer[14] == 'D' && buffer[15] == 'R') {
        // the width and height of the image are stored as 32-bit unsigned integers, so we do bitshifting to get the int number
        width = (buffer[16] << 24) | (buffer[17] << 16) | (buffer[18] << 8) | buffer[19];
        height = (buffer[20] << 24) | (buffer[21] << 16) | (buffer[22] << 8) | buffer[23];
    } else {
        printf("Error: Unable to parse PNG header\n");
        return 1;
    }

    // Convert the image to grayscale
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            unsigned char *pixel = buffer + (y * width + x) * 4;
            unsigned char gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
            pixel[0] = gray;
            pixel[1] = gray;
            pixel[2] = gray;
        }
    }

    // Open the output file
    fp = fopen("../outputImage/output.png", "wb");
    if (!fp) {
        printf("Error: Unable to open output file\n");
        return 1;
    }

    // Write the image data to the output file
    fwrite(buffer, 1, size, fp);

    // Close the output file
    fclose(fp);

    // Clean up
    free(buffer);
    return 0;
}

