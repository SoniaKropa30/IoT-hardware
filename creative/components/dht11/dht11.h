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


typedef struct s_app {
    int temp_hum[2];
    int view;
    int button1;
    int button2;
} t_app;

//void read_data_error(char * level, char *exp);
//int read_data(int time, int mode);
//void check_sum (uint8_t *bin_nbr, t_app *app);
void data_from_dht11(void *arg);

#endif
