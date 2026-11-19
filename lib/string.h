#ifndef STRING_H
#define STRING_H

#include "stddef.h"

size_t strlen(const char *str);
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
int memcmp(const void *aptr, const void *bptr, size_t n);

#endif