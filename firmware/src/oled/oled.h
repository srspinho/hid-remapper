#pragma once
#include "hardware/i2c.h"
#include <stdint.h>
#include <stdbool.h>

#define OLED_WIDTH   128
#define OLED_HEIGHT  64
#define OLED_ADDR    0x3C

void oled_init(i2c_inst_t* i2c);
void oled_update();
void oled_clear();

void oled_draw_pixel(int x, int y, bool color);
void oled_draw_char(int x, int y, char c, const uint8_t* font, 
                    uint8_t width, uint8_t height);
void oled_draw_string(int x, int y, const char* str,
                      const uint8_t* font,
                      uint8_t width, uint8_t height);
