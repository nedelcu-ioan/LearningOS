#include "string.h"
#include "algorithm.h"
#include <stdint.h>

void *memcpy(void *dest, const void *src, uint32_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (uint32_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
    return dest;
}

uint32_t strlen(const char *str) {
    uint32_t length = 0x0;
    while (str[length] != 0x0) {
        length++;
    }
    return length;
}

char *strrev(const char *str) {
    char *front = str;
    char *back = str + strlen(str) - 1;

    while (back > front)
        swap(back--, front++, 1);

    return str;
}

uint32_t strncmp(const char *a, const char *b, uint32_t n) {
    for (uint32_t i = 0; i < n; ++i) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}
