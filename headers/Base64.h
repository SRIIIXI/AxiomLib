#ifndef _BASE_64_C
#define _BASE_64_C

extern void encodebase64(const unsigned char *data, unsigned long inputlength, char *encodedString, unsigned long *outputlength);
extern void decodebase64(const char *encodedString, unsigned long inputlength, unsigned char *decodedData, unsigned long *outputlength);


#endif
