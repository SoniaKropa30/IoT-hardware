//#include "accelerometer.h"
//#include "buttons.h"
#include "dht11.h"
#include "oled.h"

void dht11_initialization() {
    gpio_set_direction(GPIO_POWER, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_DATA, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_POWER, 1);
    gpio_set_level(GPIO_DATA, 1);
    ets_delay_us(2000010);
}
void app_main() {
    t_app *apps = malloc(sizeof(t_app));
    bzero(apps, sizeof(t_app));
    dht11_initialization();
//
//    apps->temp_hum[0] = 123;
//    apps->temp_hum[1] = 456;


    xTaskCreate(data_from_dht11, "data_from_dht11", 2048,
                apps, 1, NULL);
        printf("in main %d  %d\n\n", apps->temp_hum[0], apps->temp_hum[1]);
//    xTaskCreate(data_to_oled, "data_to_oled", 4096,
//                apps, 1, NULL);

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
