#include "StringEx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define printLine printf("\n")

int main(int argc, char *argv[])
{
	char* ptr = "   aaa mmmBBB7654aaa___Hello! he&aa%xxxxaa";

	ptr = strlefttrim(ptr);

    return 0;
}
