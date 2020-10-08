#include "hardware_creative.h"

void data_from_dht11(void *arg) {
    dht11_initialization();
    t_app *app = (t_app*)arg;

    while(1) {
        sensor_activation();
        take_data_from_dht11(app->temp_hum);
            printf("%d %d\n\n", app->temp_hum[0], app->temp_hum[1]);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}