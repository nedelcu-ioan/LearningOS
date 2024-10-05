#include "algorithm.h"

void swap(void *a, void *b, uint32_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

