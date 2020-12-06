#include "oled.h"

void init_i2c() {
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 1000000
    };
    i2c_param_config(I2C_PORT, &i2c_config);
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);
}

void app_main() {
    gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_32, 1);
    init_i2c();
    sh1106_t display;
    display.addr = I2C_ADDR;
    display.port = I2C_PORT;
    oled_init(&display);
    while (true) {
        oled_clear(&display);
        oled_update(&display);
        write_to_oled(&display);
        oled_update(&display);
        vTaskDelay(500);
    }
}
