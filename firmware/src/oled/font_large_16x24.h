#ifndef FONT_LARGE_16X24_H
#define FONT_LARGE_16X24_H

#include <stdint.h>

// Fonte 16x24
// Cada caractere:
// largura = 16 pixels
// altura = 24 pixels
// 24 linhas = 3 blocos de 8 linhas
// Cada bloco contém 16 bytes (1 byte por coluna)

#define FONT_LARGE_WIDTH   16
#define FONT_LARGE_HEIGHT  24
#define FONT_LARGE_FIRST   32
#define FONT_LARGE_LAST    127

// Cada caractere ocupa:
// 16 colunas × 3 páginas = 48 bytes

extern const uint8_t font_large_16x24[];

// Função auxiliar para pegar ponteiro do caractere
static inline const uint8_t* font_large_get_char(char c)
{
    if (c < FONT_LARGE_FIRST || c > FONT_LARGE_LAST)
        return 0;

    uint16_t index = (c - FONT_LARGE_FIRST) * 48;
    return &font_large_16x24[index];
}

#endif
