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

typedef struct s_button {
    _Bool but_flag;
    _Bool turn_sw;
    int led_flag;
}              t_button;

void init_buttons();
void switch_helper(t_button *sw);

#endif
