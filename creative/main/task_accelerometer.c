#include "hardware_creative.h"

void data_from_acclerometer(void* arg) {
    t_app *apps = (t_app*)arg;
    int16_t accs[3];
    spi_device_handle_t spi;
    accel_config(&spi);

    while (1) {
        read_acceleration(spi, accs);

        if(accs[1] > 0 && apps->view == 1) {
            apps->view  = 0;
            apps->was_changed = 1;
        }
        else if(accs[1] < 0 && apps->view == 0) {
            apps->view = 1;
            apps->was_changed = 1;
        }
        else {
            apps->was_changed = 0;
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);

    }
}

