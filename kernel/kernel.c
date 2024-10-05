#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* Only for 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "tty.h"
#include "vga.h"
#include "test_string.h"
#include "test_stdlib.h";

void kernel_entrypoint(unsigned long magic, unsigned long addr) {
    terminal_init();
    test_string();
    test_itoa();
    terminal_printf("-- Done Testing --\n");
}
