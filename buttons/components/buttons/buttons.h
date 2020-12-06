#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include <driver/dac.h>
#include <stdbool.h>

#define SWP_1 39
#define SWP_2 18
#define LED_1 27
#define LED_2 26


typedef struct s_button {
    _Bool but_flag;
    _Bool turn_sw;
    int led_flag;
    int gpio_num;
}              t_button;

void init_button_ledc();

void switch_helper(t_button *sw);



#endif //HARDWARE_BUTTONS_H
