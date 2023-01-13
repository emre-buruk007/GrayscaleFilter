#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Open the input file
    FILE *fp = fopen("../inputImage/testImage.png", "rb");
    if (!fp) {
        printf("Error: Unable to open input file\n");
        return 1;
    }

    // Read the PNG header to get the width and height
    unsigned width, height;
    unsigned char header[8];   // PNG header 8 bytes
    unsigned char IHDR[25];    // IHDR chunk 25 bytes
    fread(header, 1, 8, fp);

    // PNG header standard
    if (header[0] == 137 && header[1] == 80 && header[2] == 78 && header[3] == 71 && header[4] == 13 && header[5] == 10 && header[6] == 26 && header[7] == 10) {
        fread(IHDR, 1, 8, fp);
        while(IHDR[4] != 'I' && IHDR[5] != 'H' && IHDR[6] != 'D' && IHDR[7] != 'R')
        {
            fread(IHDR, 1, 8, fp);
        }

        // bad calculaton here
        width = (IHDR[4] << 24) | (IHDR[5] << 16) | (IHDR[6] << 8) | IHDR[7];
        height = (IHDR[8] << 24) | (IHDR[9] << 16) | (IHDR[10] << 8) | IHDR[11];
    } else {
        printf("Error: Input file is not a valid PNG image\n");
        return 1;
    }
    size_t size = width*height*3;
    unsigned char *image_data = malloc(size);
    fread(image_data, 1, size, fp);

    // Close the input file
    fclose(fp);

    // Check the size of the image data in the buffer
    if(size == 0)
    {
        printf("Error: Image data is empty or corrupted\n");
        return 1;
    }
    // Convert the image to grayscale
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            unsigned char *pixel = image_data + (y * width + x) * 3;
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
    if(fwrite(image_data, 1, size, fp) != size)
    {
        printf("Error: Unable to write image data to output file\n");
        return 1;
    }

    // Close the output file
    fclose(fp);

    // Check for errors
    if(ferror(fp))
    {
        printf("Error: An error occurred during the file operation\n");
        return 1;
    }

    // Clean up
    free(image_data);
    return 0;
}



