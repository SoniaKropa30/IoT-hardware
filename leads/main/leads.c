#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include <unistd.h>

#define GPIO_LED_1 27
#define GPIO_LED_2 26
#define GPIO_LED_3 33

void app_main() {
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_LED_1, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_LED_2, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_LED_3, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_LED_1, 1));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_LED_2, 1));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_LED_3, 1));
}
