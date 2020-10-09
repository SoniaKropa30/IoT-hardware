#include "hardware_creative.h"

static void orientation (t_app *apps, t_display *display) {

    apps->was_changed = 0;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (display->addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x0, true); // command stream
    i2c_master_write_byte(cmd, 0xAE, true); // off

    if(apps->view == 1) {
        ESP_ERROR_CHECK(i2c_master_write_byte(cmd, 0xA1, true));
        ESP_ERROR_CHECK(i2c_master_write_byte(cmd, 0xC8, true));
    }
    else {
        i2c_master_write_byte(cmd, 0xA0, true); // for vertical view
        i2c_master_write_byte(cmd, 0xC0, true);
    }
    i2c_master_write_byte(cmd, 0xAF, true); // on
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(display->port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

}

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
    char str[17];
    bzero(&str, sizeof(str));
    oled_clear(display);
    oled_update(display, str);


    while (1) {
        if (apps->temp_hum[0] && apps->temp_hum[1]) {
            if (apps->was_changed)
                orientation(apps, display);
            if (apps->button1 || (!apps->button1 && !apps->button2))
                sprintf(str, "Temperature: %dC", apps->temp_hum[0]);
            else
                sprintf(str, "Humidity: %d%%", apps->temp_hum[1]);
            oled_clear(display);
            oled_update(display, str);
            write_to_oled(display, str);
            oled_update(display, str);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else
            vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}