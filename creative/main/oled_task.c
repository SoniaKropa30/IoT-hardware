#include "hardware_creative.h"

void data_to_oled(void *arg) {
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_32, 1));
    init_i2c();
    t_app *apps = (t_app*)arg;
    t_display *display = malloc(sizeof(t_display));

    display->font_str = (uint8_t*)malloc(sizeof(uint8_t) * (128 * 8));
    bzero(display->font_str, SCREEN_SIZE);
    display->addr = I2C_ADDR;
    display->port = I2C_PORT;
    oled_initialization(display);

    char t[17];
    char h[15];
//    printf("in oled %d   %d \n\n", apps->temp_hum[0], apps->temp_hum[1]);
    while (1) {
        sprintf(t, "Temperature: %dC", apps->temp_hum[0]);
        sprintf(h, "Humidity: %d%%", apps->temp_hum[1]);
        oled_clear(display);
        oled_update(display, h);
        write_to_oled(display, h);
        oled_update(display, h);
        vTaskDelay(2000/portTICK_PERIOD_MS); // todo chek delay
    }
}