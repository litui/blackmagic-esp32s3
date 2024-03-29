#include "led.h"
#include "math.h"
#include <driver/ledc.h>
#include <esp_log.h>
#include <esp_err.h>

#if defined(CONFIG_BOARD_TDISPLAY_S3_AMOLED)
#define LED_PIN_RED (-1)
#define LED_PIN_GREEN (38)
#define LED_PIN_BLUE (-1)
#else
#define LED_PIN_RED (-1)
#define LED_PIN_GREEN (-1)
#define LED_PIN_BLUE (-1)
#endif

#define LEDC_MODE LEDC_LOW_SPEED_MODE

#define LED_PWM_MAX_VAL 256U

#define LED_RED_MAX_VAL 20U
#define LED_GREEN_MAX_VAL 20U
#define LED_BLUE_MAX_VAL 20U

static const char* TAG = "led";

typedef enum {
    LedChannelRed,
    LedChannelGreen,
    LedChannelBlue,
} ledc_channel;

void led_init() {
    ESP_LOGI(TAG, "init");
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000, // Set output frequency at 5 kHz
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

#if LED_PIN_RED != -1
    ledc_channel_config_t ledc_channel_red = {
        .speed_mode = LEDC_MODE,
        .channel = LedChannelRed,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_PIN_RED,
        .duty = LED_PWM_MAX_VAL, // Set duty to 100%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_red));
#endif

#if LED_PIN_GREEN != -1
    ledc_channel_config_t ledc_channel_green = {
        .speed_mode = LEDC_MODE,
        .channel = LedChannelGreen,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_PIN_GREEN,
        .duty = LED_PWM_MAX_VAL, // Set duty to 100%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_green));
#endif

#if LED_PIN_BLUE != -1
    ledc_channel_config_t ledc_channel_blue = {
        .speed_mode = LEDC_MODE,
        .channel = LedChannelBlue,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_PIN_BLUE,
        .duty = LED_PWM_MAX_VAL, // Set duty to 100%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_blue));
#endif
    ESP_LOGI(TAG, "init done");
}

void led_set(uint8_t red, uint8_t green, uint8_t blue) {
    led_set_red(red);
    led_set_green(green);
    led_set_blue(blue);
}

void led_set_red(uint8_t value) {
#if LED_PIN_RED != -1
    uint32_t pwm_value = ((uint32_t)value * LED_RED_MAX_VAL) / 255;
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LedChannelRed, pwm_value > LED_PWM_MAX_VAL ? LED_PWM_MAX_VAL : pwm_value));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LedChannelRed));
#else
    led_set_green(value);
#endif
}

void led_set_green(uint8_t value) {
#if LED_PIN_GREEN != -1
    uint32_t pwm_value = ((uint32_t)value * LED_GREEN_MAX_VAL) / 255;
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LedChannelGreen, pwm_value > LED_PWM_MAX_VAL ? LED_PWM_MAX_VAL : pwm_value));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LedChannelGreen));
#endif
}

void led_set_blue(uint8_t value) {
#if LED_PIN_BLUE != -1
    uint32_t pwm_value = ((uint32_t)value * LED_BLUE_MAX_VAL) / 255;
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LedChannelBlue, pwm_value > LED_PWM_MAX_VAL ? LED_PWM_MAX_VAL : pwm_value));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LedChannelBlue));
#else
    led_set_green(value);
#endif
}
