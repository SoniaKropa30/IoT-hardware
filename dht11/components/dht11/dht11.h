#ifndef DHT11_H
#define DHT11_H

#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include <driver/dac.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>

#define GPIO_POWER 2
#define GPIO_DATA 4

//void sensor_activation(void);
//void check_sum (uint8_t *bin_nbr);
void data_from_dht11(void *arg);
#endif
