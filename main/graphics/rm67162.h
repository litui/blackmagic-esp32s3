#pragma once

#include "stdint.h"
#include "driver/spi_master.h"

/***********************config*************************/
#define SPI_FREQUENCY         75000000
#define TFT_SPI_MODE          SPI_TRANS_MODE_QIO
#define TFT_SPI_HOST          SPI2_HOST

#define LCD_H_RES     536
#define LCD_V_RES     240
#define LVGL_LCD_BUF_SIZE     (LCD_H_RES * LCD_V_RES) * 2

/***********************config*************************/

#define TFT_WIDTH             240
#define TFT_HEIGHT            536
#define SEND_BUF_SIZE         (0x4000) //(LCD_WIDTH * LCD_HEIGHT + 8) / 10

#define TFT_TE                9
#define TFT_SDO               8

#define TFT_DC                7
#define TFT_RES               17
#define TFT_CS                6
#define TFT_MOSI              18
#define TFT_SCK               47

#define TFT_QSPI_CS           6
#define TFT_QSPI_SCK          47
#define TFT_QSPI_D0           18
#define TFT_QSPI_D1           7
#define TFT_QSPI_D2           48
#define TFT_QSPI_D3           5
#define TFT_QSPI_RST          17

#define PIN_LED               38
#define PIN_BAT_VOLT          4

#define PIN_BUTTON_1          0
#define PIN_BUTTON_2          21

#define TFT_MADCTL 0x36
#define TFT_MAD_MY 0x80
#define TFT_MAD_MX 0x40
#define TFT_MAD_MV 0x20
#define TFT_MAD_ML 0x10
#define TFT_MAD_BGR 0x08
#define TFT_MAD_MH 0x04
#define TFT_MAD_RGB 0x00

#define TFT_INVOFF 0x20
#define TFT_INVON 0x21

typedef struct {
    uint8_t cmd;
    uint8_t data[4];
    uint8_t len;
} lcd_cmd_t;

void rm67162_init(void);

// Set the display window size
void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void lcd_setRotation(uint8_t r);
void lcd_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void lcd_fill(uint16_t xsta,
              uint16_t ysta,
              uint16_t xend,
              uint16_t yend,
              uint16_t color);
void lcd_PushColors(uint16_t x,
                    uint16_t y,
                    uint16_t width,
                    uint16_t high,
                    uint16_t *data);
void lcd_PushColorsSimple(uint16_t *data, uint32_t len);
void lcd_sleep();