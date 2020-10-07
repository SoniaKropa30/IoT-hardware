#ifndef PWM_DAC_H
#define PWM_DAC_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include <driver/dac.h>

#define GPIO_LED_1 27
#define MAX_DUTY 255
#define MIN_FADE 0
#define FADE_TIME 3000

void DAC_method(void);
void PWM_method(ledc_channel_config_t *ledc_channel);
void init_timer_chanel(ledc_timer_config_t *ledc_timer,
                       ledc_channel_config_t *ledc_channel);

#endif