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
#include "freertos/queue.h"

#define GPIO_POWER 2
#define GPIO_DATA 4

QueueHandle_t dht11_queue;

struct s_message {
    int temperature;
    int humidity;
} xMessage;


void dht11_initialization(void);
void sensor_activation(void);
int take_data_from_dht11(int *temp_hum);

#endif
