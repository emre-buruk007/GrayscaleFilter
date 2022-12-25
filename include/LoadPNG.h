#ifndef GRAYSCALEFILTER_LOADPNG_H
#define GRAYSCALEFILTER_LOADPNG_H

/**
 * This function checks whether the passed equation is true or not, thus verifying whether
 * the given byte value is valid for a PNG header.
 * @param val boolean coming from function call
 * @param msg Identifying the current byte.
 */
void validate(int val, const char *msg);

/**
 * This function checks the header of the opened file to make sure it is indeed a PNG.
 * @param buf the image in string format
 */
void checkHeader(const char *buf);


int readPng();


#endif //GRAYSCALEFILTER_LOADPNG_H
