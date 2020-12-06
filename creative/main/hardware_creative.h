#ifndef HARDWARE_CREATIVE_H
#define HARDWARE_CREATIVE_H

#include "accelerometer.h"
#include "buttons.h"
#include "dht11.h"
#include "oled.h"

typedef struct s_app {
    int temp_hum[2];
    int view;
    _Bool was_changed;
    _Bool button1;
    _Bool button2;
} t_app;

void data_from_dht11(void *arg);
void data_to_oled(void *arg);
void data_from_acclerometer(void* arg);
void data_from_buttons(void *arg);

#endif
