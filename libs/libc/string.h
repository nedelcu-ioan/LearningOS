#pragma once

#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, uint32_t n);
uint32_t strlen(const char *str);
char *strrev(const char *str);
uint32_t strncmp(const char *a, const char *b, uint32_t n);
