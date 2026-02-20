#pragma once
#include <stdint.h>
#include "hardware/i2c.h"   // <-- FALTAVA ISSO

#define OLED_WIDTH   128
#define OLED_HEIGHT   64

#ifdef __cplusplus
extern "C" {
#endif

//void oled_init(void);
void oled_init(i2c_inst_t* i2c);
void oled_clear(void);
void oled_update(void);

void oled_draw_string(int x, int y,
                      const char* str,
                      const uint8_t* font,
                      uint8_t width,
                      uint8_t height);

#ifdef __cplusplus
}
#endif
