#include "display.h"
#include "esp_log.h"
// #include "framebuffer.h"
// #if defined(CONFIG_RM67162_GRAPHICS)
// #include "graphics/rm67162.h"
// #endif

#include <hagl_hal.h>
#include <hagl.h>

static const char* TAG = "display";

hagl_backend_t *disp;

// framebuffer_t display_fb;

// uint16_t rgb_to_16bit(rgb_t rgb) {
//     return (rgb.red >> 3 << 11) + (rgb.green >> 2 << 5) + (rgb.blue >> 3);
// }

// static esp_err_t render_frame(framebuffer_t *fb, void *arg) {
//     for (uint32_t i = 0; i < fb->width * fb->height; i++) {
//         uint16_t x = i % fb->width;
//         uint16_t y = i / fb->width;
//         lcd_DrawPoint(x, y, rgb_to_16bit(fb->data[i]));
//     }
//     return 0;
// }

void display_init() {
    ESP_LOGI(TAG, "init");
#if defined(CONFIG_RM67162_GRAPHICS)

    ESP_LOGI(TAG, "mallocing driver");
    disp = (hagl_backend_t*) malloc(sizeof(hagl_backend_t));
    ESP_LOGI(TAG, "initing driver");
    disp = hagl_init();

    ESP_LOGI(TAG, "clearing display");
    hagl_clear(disp);
    ESP_LOGI(TAG, "flushing display");
    hagl_flush(disp);

    ESP_LOGI(TAG, "drawing lines");
for (uint16_t i = 1; i < 10; i++) {
    int16_t x0 = rand() % disp->width;
    int16_t y0 = rand() % disp->height;
    int16_t x1 = rand() % disp->width;
    int16_t y1 = rand() % disp->height;
    hagl_color_t color = rand() % 0xffff;

    hagl_draw_line(disp, x0, y0, x1, y1, color);
}

    // rm67162_init();
    // fb_init(&display_fb, TFT_WIDTH, TFT_HEIGHT, render_frame);

    // rgb_t colour = {
    //     .red = 255,
    //     .green = 255,
    //     .blue = 255
    // };
    // fb_set_pixel_rgb(&display_fb, 10, 10, colour);

    // fb_render(&display_fb, NULL);

#endif
    ESP_LOGI(TAG, "end init");
}
