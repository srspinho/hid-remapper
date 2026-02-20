#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void oled_init(void);
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
