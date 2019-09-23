#include "Base64.h"
#include <memory.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>

const char encodingtable[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
								'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
								'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
								'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
								'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
								'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
								'w', 'x', 'y', 'z', '0', '1', '2', '3',
								'4', '5', '6', '7', '8', '9', '+', '/' };

const int modulustable[] = { 0, 2, 1 };


void encodebase64(const unsigned char *data, unsigned long inputlength, char *encodedString, unsigned long *outputlength)
{
	*outputlength = 4 * ((inputlength + 2) / 3);

	encodedString = (char*)calloc(1, (size_t)(*outputlength) + 1);

	if (encodedString == NULL)
	{
		outputlength = 0;
		return;
	}

	for (unsigned int i = 0, j = 0; i < inputlength;)
	{

		uint32_t octet_a = i < inputlength ? (unsigned char)data[i++] : 0;
		uint32_t octet_b = i < inputlength ? (unsigned char)data[i++] : 0;
		uint32_t octet_c = i < inputlength ? (unsigned char)data[i++] : 0;

		uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		encodedString[j++] = encodingtable[(triple >> 3 * 6) & 0x3F];
		encodedString[j++] = encodingtable[(triple >> 2 * 6) & 0x3F];
		encodedString[j++] = encodingtable[(triple >> 1 * 6) & 0x3F];
		encodedString[j++] = encodingtable[(triple >> 0 * 6) & 0x3F];
	}

	for (int i = 0; i < modulustable[inputlength % 3]; i++)
	{
		encodedString[*outputlength - 1 - i] = '=';
	}

	return;
}


void decodebase64(const char *encodedString, unsigned long inputlength, unsigned char *decodedData, unsigned long *outputlength)
{
	char decodingtable[256] = { 0 };

	for (int i = 0; i < 64; i++)
	{
		decodingtable[(unsigned char)encodingtable[i]] = i;
	}

	if (inputlength % 4 != 0) return;

	*outputlength = inputlength / 4 * 3;

	if (encodedString[inputlength - 1] == '=') (*outputlength)--;
	if (encodedString[inputlength - 2] == '=') (*outputlength)--;

	decodedData = (unsigned char*)calloc(1, *outputlength);

	if (decodedData == NULL)
	{
		*outputlength = 0;
		return;
	}

	for (unsigned int i = 0, j = 0; i < inputlength;)
	{
		uint32_t sextet_a = encodedString[i] == '=' ? 0 & i++ : decodingtable[encodedString[i++]];
		uint32_t sextet_b = encodedString[i] == '=' ? 0 & i++ : decodingtable[encodedString[i++]];
		uint32_t sextet_c = encodedString[i] == '=' ? 0 & i++ : decodingtable[encodedString[i++]];
		uint32_t sextet_d = encodedString[i] == '=' ? 0 & i++ : decodingtable[encodedString[i++]];

		uint32_t triple = (sextet_a << 3 * 6)
			+ (sextet_b << 2 * 6)
			+ (sextet_c << 1 * 6)
			+ (sextet_d << 0 * 6);

		if (j < *outputlength) decodedData[j++] = (triple >> 2 * 8) & 0xFF;
		if (j < *outputlength) decodedData[j++] = (triple >> 1 * 8) & 0xFF;
		if (j < *outputlength) decodedData[j++] = (triple >> 0 * 8) & 0xFF;
	}

	return;
}
