#include "hardware_creative.h"

void data_from_acclerometer(void* arg) {
    t_app *apps = (t_app*)arg;
    int16_t accs[3];
    spi_device_handle_t spi;
    accel_config(&spi);

    while (1) {
        read_acceleration(spi, accs);
//        printf("xyz %d      %d      %d\n", (int)accs[0], (int)accs[1], (int)accs[2]);

        if(accs[2] > 0)
            apps->view  = 0;
        else
            apps->view  = 1;
        printf("ACCELEROMETER = %d\n", apps->view);
        vTaskDelay(10);
    }
}

