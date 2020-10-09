#include "dht11.h"

void app_main() {
    xTaskCreate(data_from_dht11, "data_from_dht11", 2048,
                NULL, 1, NULL);

}

