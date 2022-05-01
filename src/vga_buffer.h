#include <stdint.h>
#include "helpers.h"

volatile uint16_t *vga_buffer = (uint16_t*) 0xB8000;
volatile uint16_t *tmp_vga_buffer = (uint16_t*) 0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0, term_row = 0;
uint8_t term_color = 0x0F; // FFFFBBBB(CCCC)

void term_init();
void term_putc(char);
void term_putc_color(char, uint8_t);
void term_print(const char*);
void term_rainbow();
void color_increase(uint16_t*);

void term_init() 
{ 
    for (int c = 0; c < VGA_COLS; c++) {
        for (int r = 0; r < VGA_ROWS; r++) {
            const size_t i = (VGA_COLS * r) + c;
            vga_buffer[i] = ((uint16_t)term_color << 8) | ' ';
        }
    }
    term_print("Hello World, from my first kernel");
    for (int i = 0; i < 24; i++) term_print("\n");
    term_print("~Cainan Travizanutto, 2022");
    _sleep(500000000);
}

void term_putc(char c) 
{
    switch (c) {
        case '\n': {
            term_col = 0;
            term_row++; break;
        }
        default: {
            const size_t i = (VGA_COLS * term_row) + term_col;
            vga_buffer[i] = ((uint16_t)term_color << 8) | c;
            term_col++; break;
        }
    }

    if (term_col >= VGA_COLS) { 
        term_col = 0;
        term_row++;
    }
    if (term_row >= VGA_COLS) {
        term_col = 0;
        term_row = 0;
    }
}

void term_putc_color(char c, uint8_t color) 
{
   const size_t i = (VGA_COLS * term_row) + term_col;
    vga_buffer[i] = ((uint16_t)color << 8) | c;
    term_col++;

    if (term_col >= VGA_COLS) { 
        term_col = 0;
        term_row++;
    }
    if (term_row >= VGA_COLS) {
        term_col = 0;
        term_row = 0;
    }
}

void term_print(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        term_putc(str[i]);
    }
    
}

void term_rainbow()
{   
    uint16_t color = (uint16_t) 0x1 << 4;
    uint16_t *col = &color;
    while (1) {
        color_increase(col);
        for (int r = 0; r < VGA_ROWS; r++) {
            for (int c = 0; c < VGA_COLS; c++) {
                vga_buffer[VGA_COLS * r + c] = *col << 8;   
            }
            color_increase(col);
        } _sleep(7500000);
    }
}

void color_increase(uint16_t *c) {
    if (*c == 0xf << 4) *c = 0x1 << 4;
    else *c += 0x1 << 4;
}