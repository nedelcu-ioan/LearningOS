#pragma once
#include "kernel/panic.h"
#include "kernel/tty.h"

#ifdef NDEBUG
#define ASSERT(expression)                                                     \
    ((void)0) // Assertions are disabled in release builds
#else
#define ASSERT(expression)                                                     \
    do {                                                                       \
        if (!(expression)) {                                                   \
            terminal_printf("Assertion failed: %s\n", #expression);            \
            terminal_printf("In file: %s, on line: %d\n", __FILE__, __LINE__); \
            panic();                                                           \
        } else {                                                               \
            terminal_printf("Assertion passed: %s\n", #expression);            \
        }                                                                      \
    } \
while (0)
#endif
