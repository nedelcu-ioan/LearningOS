#include "assert.h"
#include "stdlib.h"
#include "string.h"
#include "stddef.h"

void test_itoa() {
    char nr[32];
    ASSERT(strncmp(itoa(12, nr, 10), "12", 2) == 1);
    ASSERT(strncmp(itoa(-12, nr, 10), "-12", 2) == 1);
    ASSERT(strncmp(itoa(3, nr, 2), "11", 2) == 1);
    ASSERT(strncmp(itoa(-3, nr, 10), "-3", 2) == 1);
    ASSERT(strncmp(itoa(13, nr, 10), "12", 2) == 0);
}
