#include "tty.h"
#include "vga.h"
#include "stdlib.h"

uint32_t x_pos;
uint32_t y_pos;
uint8_t terminal_color;
volatile uint16_t *video;

void terminal_set_color(uint8_t color) { terminal_color = color; }

void terminal_cls(void) {
    video = (uint16_t *)VIDEO;
    for (int i = 0; i < COLUMNS * LINES; ++i) {
        video[i] = 0;
    }
    x_pos = 0;
    y_pos = 0;
}

void terminal_init(void) {
    terminal_set_color(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_CYAN));
    terminal_cls();
}

void terminal_putchar(char c) {
    const unsigned index = y_pos * COLUMNS + x_pos;
    video[index] = vga_entry(c, terminal_color);
    ++x_pos;

    if (COLUMNS <= x_pos) {
        goto newline;
    }

    if ('\n' == c || '\r' == c) {
    newline:
        x_pos = 0;
        ++y_pos;
        if (LINES <= y_pos) {
            y_pos = 0;
            return;
        }
    }
}

void terminal_puts(const char *s) {
    while (*s) {
        terminal_putchar(*s++);
    }
}

void terminal_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;

            switch (*format) {
            case 'd': {
                int i = va_arg(args, int);
                char nr[32];
                terminal_puts(itoa(i, nr, 10));
                break;
            }
            case 's': {
                char *s = va_arg(args, char *);
                terminal_puts(s);
                break;
            }
            default:
                terminal_putchar('%');
                terminal_putchar(*format);
                break;
            }
        } else {
            terminal_putchar(*format);
        }
        format++;
    }

    va_end(args);
}

void terminal_scroll(uint32_t line) {}
