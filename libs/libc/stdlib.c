#include "stdlib.h"
#include "algorithm.h"

char *itoa(int number, char *buffer, int base) {
    if (base < 2 || base > 16) {
        buffer[0] = '\0';
        return buffer;
    }

    int i = 0, isNegative = 0;

    if (number < 0 && base == 10) {
        isNegative = 1;
        number = -number;
    }

    do {
        int remainder = number % base;
        buffer[i++] =
            (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        number = number / base;
    } while (number != 0);

    if (isNegative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';
    strrev(buffer);

    return buffer;
}
