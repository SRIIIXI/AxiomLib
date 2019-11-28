#ifndef _BASE_64_C
#define _BASE_64_C

void encode_base64(const unsigned char *data, unsigned long inputlength, char *encodedString, unsigned long *outputlength);
void decode_base64(const char *encodedString, unsigned long inputlength, unsigned char *decodedData, unsigned long *outputlength);


#endif
