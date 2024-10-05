#pragma once

#include <stdint.h>
#include <stddef.h>

#define COLUMNS 80
#define LINES 24
#define VIDEO 0xB8000

extern uint32_t x_pos;
extern uint32_t y_pos;
extern uint8_t terminal_color;
extern volatile uint16_t *video;

void terminal_set_color(uint8_t color);
void terminal_cls(void);
void terminal_init(void);
void terminal_putchar(char c);
void terminal_printf(const char *format, ...);
void terminal_scroll(uint32_t line);

