#include "oled.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define SDA_PIN 20
#define SCL_PIN 21

#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_HEIGHT / 8)

static uint8_t oled_buffer[OLED_BUFFER_SIZE];

static i2c_inst_t* oled_i2c;

static void oled_write_cmd(uint8_t cmd)
{
    uint8_t buf[2] = {0x00, cmd};
    i2c_write_blocking(oled_i2c, OLED_ADDR, buf, 2, false);
}

static void oled_write_data(uint8_t* data, size_t len)
{
    uint8_t temp[129];
    temp[0] = 0x40;

    for (size_t i = 0; i < len; i++)
        temp[i + 1] = data[i];

    i2c_write_blocking(oled_i2c, OLED_ADDR, temp, len + 1, false);
}

void oled_init(i2c_inst_t* i2c)
{
    oled_i2c = i2c;

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(100);

    oled_write_cmd(0xAE); // Display off
    oled_write_cmd(0x20); oled_write_cmd(0x00);
    oled_write_cmd(0xB0);
    oled_write_cmd(0xC8);
    oled_write_cmd(0x00);
    oled_write_cmd(0x10);
    oled_write_cmd(0x40);
    oled_write_cmd(0x81); oled_write_cmd(0x7F);
    oled_write_cmd(0xA1);
    oled_write_cmd(0xA6);
    oled_write_cmd(0xA8); oled_write_cmd(0x3F);
    oled_write_cmd(0xA4);
    oled_write_cmd(0xD3); oled_write_cmd(0x00);
    oled_write_cmd(0xD5); oled_write_cmd(0xF0);
    oled_write_cmd(0xD9); oled_write_cmd(0x22);
    oled_write_cmd(0xDA); oled_write_cmd(0x12);
    oled_write_cmd(0xDB); oled_write_cmd(0x20);
    oled_write_cmd(0x8D); oled_write_cmd(0x14);
    oled_write_cmd(0xAF); // Display on

    oled_clear();
    oled_update();
}

void oled_update()
{
    for (uint8_t page = 0; page < 8; page++)
    {
        oled_write_cmd(0xB0 + page);
        oled_write_cmd(0x00);
        oled_write_cmd(0x10);

        oled_write_data(&oled_buffer[OLED_WIDTH * page], OLED_WIDTH);
    }
}

void oled_clear()
{
    for (int i = 0; i < OLED_BUFFER_SIZE; i++)
        oled_buffer[i] = 0;
}

void oled_draw_pixel(int x, int y, bool color)
{
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT)
        return;

    uint16_t index = x + (y / 8) * OLED_WIDTH;

    if (color)
        oled_buffer[index] |= (1 << (y % 8));
    else
        oled_buffer[index] &= ~(1 << (y % 8));
}

void oled_draw_char(int x, int y, char c,
                    const uint8_t* font,
                    uint8_t width, uint8_t height)
{
    uint16_t offset = (c - 32) * width * (height / 8);

    for (uint8_t col = 0; col < width; col++)
    {
        for (uint8_t row = 0; row < height; row++)
        {
            uint16_t byte_index = offset + col + (row / 8) * width;
            bool pixel = font[byte_index] & (1 << (row % 8));
            oled_draw_pixel(x + col, y + row, pixel);
        }
    }
}

void oled_draw_string(int x, int y,
                      const char* str,
                      const uint8_t* font,
                      uint8_t width,
                      uint8_t height)
{
    while (*str)
    {
        oled_draw_char(x, y, *str, font, width, height);
        x += width;
        str++;
    }
}
