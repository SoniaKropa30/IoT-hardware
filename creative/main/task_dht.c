#include "hardware_creative.h"

void data_from_dht11(void *arg) {
    dht11_initialization();
    t_app *apps = (t_app*)arg;

    while(1) {
        sensor_activation();
        take_data_from_dht11(apps->temp_hum);
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}