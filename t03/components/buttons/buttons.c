#include "buttons.h"

static void print_error() {
    write(2, "ESP_ERR_INVALID_ARG GPIO is not an RTC IO\n", 21);
    exit(1);
}

void init_button_ledc() {
    if (gpio_set_direction(SWP_1, GPIO_MODE_INPUT) == ESP_ERR_INVALID_ARG)
        print_error();
    if (gpio_set_direction(SWP_2, GPIO_MODE_INPUT) == ESP_ERR_INVALID_ARG)
       print_error();
    if (gpio_set_direction(LED_1, GPIO_MODE_OUTPUT) == ESP_ERR_INVALID_ARG)
        print_error();
    if (gpio_set_direction(LED_2, GPIO_MODE_OUTPUT) == ESP_ERR_INVALID_ARG)
        print_error();
}

void switch_helper(t_button *sw) {
    if(sw->turn_sw == 0 && sw->but_flag == false)
        sw->but_flag = 1;
    if(sw->turn_sw == 1 && sw->but_flag == 1) {
        sw->but_flag = !sw->but_flag;
        sw->led_flag = !sw->led_flag;
        if(sw->led_flag)
            gpio_set_level(sw->gpio_num, 1); //ESP_ERR_INVALID_ARG GPIO is not an RTC IO
        else
            gpio_set_level(sw->gpio_num, 0);
    }
}

