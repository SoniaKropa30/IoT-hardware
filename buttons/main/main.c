#include "buttons.h"

void app_main() {
    init_button_ledc();
    t_button sw1 = (t_button){0, 1, 0, LED_1};
    t_button sw2 = (t_button){0, 1, 0, LED_2};

    while (1) {
        sw1.turn_sw = gpio_get_level(SWP_1);
        sw2.turn_sw = gpio_get_level(SWP_2);
        switch_helper(&sw1);
        switch_helper(&sw2);
        vTaskDelay(10);
    }
}
