#include "buttons.h"

static void print_error() {
    write(2, "ESP_ERR_INVALID_ARG GPIO is not an RTC IO\n", 21);
    exit(1);
}

void init_buttons() {
    if (gpio_set_direction(SWP_1, GPIO_MODE_INPUT) == ESP_ERR_INVALID_ARG)
        print_error();
    if (gpio_set_direction(SWP_2, GPIO_MODE_INPUT) == ESP_ERR_INVALID_ARG)
       print_error();
}

void switch_helper(t_button *sw) {
    if(sw->turn_sw == 0 && sw->but_flag == false)
        sw->but_flag = 1;
    if(sw->turn_sw == 1 && sw->but_flag == 1) {
        sw->but_flag = !sw->but_flag;
        sw->led_flag = !sw->led_flag;
        if(sw->led_flag)
           printf("write to oled temperature\n"); //ESP_ERR_INVALID_ARG GPIO is not an RTC IO
        else
            printf("write to oled humidity\n"); //ESP_ERR_INVALID_ARG GPIO is not an RTC IO
    }
}

void check_press_buttons() {
    init_buttons();
    t_button sw1 = (t_button){0, 1, 0};
    t_button sw2 = (t_button){0, 1, 0};

    while (1) {
        sw1.turn_sw = gpio_get_level(SWP_1);
        sw2.turn_sw = gpio_get_level(SWP_2);
        if(sw2.turn_sw)
            printf("write to oled humidity\n");
        else
            printf("write to oled temperature\n");
        vTaskDelay(10);
    }
}

