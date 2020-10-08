#include "hardware_creative.h"

void app_main() {
    t_app *apps = malloc(sizeof(t_app));
    bzero(apps, sizeof(t_app));

    xTaskCreate(data_from_dht11, "data_from_dht11", 2048,
                apps, 1, NULL);

//
//    xTaskCreate(data_from_buttons, "data_from_buttons", 2048,
//                apps, 1, NULL);
//
//
    xTaskCreate(data_from_acclerometer, "data_from_acclerometer", 4096,
                apps, 1, NULL);
    xTaskCreate(data_to_oled, "data_to_oled", 4096,
                apps, 1, NULL);


}
























//
//
//void app_main() {
////    t_app *apps = malloc(sizeof(t_app));
//    printf("hellloooo\n\n");
//    int dht11_data[2];
//    data_from_dht11(dht11_data);
//    printf("after dht11_data\n\n");
//    vTaskDelay(10000);
//    data_to_oled(NULL);
//
////  sprintf(str,"Humidity: %d %%^M", dht11_data[1]);
////  sprintf(str_to_oled,"Temperature: %d C^M", dht11_data[0]);
//
//
//
//
//
////    printf("Temperature: %d C^M\nHumidity: %d %%^M\n", dht11_data[0], dht11_data[1]);
//}
