#include "buttons.h"

void amplyfier_and_button_init() {
    gpio_set_direction(SWP_1, GPIO_MODE_INPUT);
    gpio_set_direction(SWP_2, GPIO_MODE_INPUT);
    ESP_ERROR_CHECK(dac_output_enable(DAC_CHANNEL_1));
    ESP_ERROR_CHECK(gpio_set_direction(5, GPIO_MODE_OUTPUT)); // AMPLYFIER
    ESP_ERROR_CHECK(gpio_set_direction(5, 1)); // AMPLYFIER
}

void beeep() {
    int duration = 100;
    int voltage = 100;
    float  frequency = 5;
    int delay = 20;

    while (duration > 0) {
        for (float i = 0; i < voltage; i+= frequency) {
            dac_output_voltage(DAC_CHANNEL_1, i);
            ets_delay_us(delay);
        }
        duration--;
        ets_delay_us(10);
    }
    vTaskDelay(10);
}


