#include "string.h"
#include "stddef.h"

void *memset(void *s, int c, size_t n) {
	unsigned char *buf = (unsigned char*) s;

	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char) c;

	return s;
}

void *memcpy(void *dest, const void *src, size_t n) {
	unsigned char *to = (unsigned char*) dest;
	const unsigned char *from = (const unsigned char*) src;

	for (size_t i = 0; i < n; i++)
		to[i] = from[i];

	return dest;
}

int memcmp(const void *aptr, const void *bptr, size_t n) {
	const unsigned char *a = (const unsigned char*) aptr;
	const unsigned char *b = (const unsigned char*) bptr;

	for (size_t i = 0; i < n; i++) {
		if (a[i] != b[i])
			return a[i] - b[i];
	}

	return 0;
}

size_t strlen(const char *str) {
    size_t len = 0;

    while (str[len]) 
        len++;

    return len;
}