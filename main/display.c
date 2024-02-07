#include "display.h"
#include "esp_log.h"
#include "framebuffer.h"
#if defined(CONFIG_RM67162_GRAPHICS)
#include "graphics/rm67162.h"
#endif

static const char* TAG = "display";

framebuffer_t display_fb;

uint16_t rgb_to_16bit(rgb_t rgb) {
    return (rgb.red >> 3 << 11) + (rgb.green >> 2 << 5) + (rgb.blue >> 3);
}

static esp_err_t render_frame(framebuffer_t *fb, void *arg) {
    for (uint32_t i = 0; i < fb->width * fb->height; i++) {
        uint16_t x = i % fb->width;
        uint16_t y = i / fb->width;
        lcd_DrawPoint(x, y, rgb_to_16bit(fb->data[i]));
    }
    return 0;
}

void display_init() {
    ESP_LOGI(TAG, "init");
#if defined(CONFIG_RM67162_GRAPHICS)
    rm67162_init();
    fb_init(&display_fb, TFT_WIDTH, TFT_HEIGHT, render_frame);

    rgb_t colour = {
        .red = 255,
        .green = 255,
        .blue = 255
    };
    fb_set_pixel_rgb(&display_fb, 10, 10, colour);

    // fb_render(&display_fb, NULL);

#endif
    ESP_LOGI(TAG, "end init");
}
