#include "string.h"
#include "assert.h"

void test_string() {
    ASSERT(strlen("Ana") == 3);
    ASSERT(strlen("") == 0);
}
