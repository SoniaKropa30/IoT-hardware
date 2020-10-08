#include "buttons.h"

//static void switch_helper(t_button *sw) {
//    if(sw->turn_sw == 0 && sw->but_flag == false)
//        sw->but_flag = 1;
//    if(sw->turn_sw == 1 && sw->but_flag == 1) {
//        sw->but_flag = !sw->but_flag;
//        sw->led_flag = !sw->led_flag;
////        if(sw->led_flag)
////           printf("write to oled temperature\n"); //ESP_ERR_INVALID_ARG GPIO is not an RTC IO
////        else
////            printf("write to oled humidity\n"); //ESP_ERR_INVALID_ARG GPIO is not an RTC IO
//    }
//}
//
//void amplyfier_and_button_init() {
//    gpio_set_direction(SWP_1, GPIO_MODE_INPUT);
//    gpio_set_direction(SWP_2, GPIO_MODE_INPUT);
//    ESP_ERROR_CHECK(dac_output_enable(DAC_CHANNEL_1));
//    ESP_ERROR_CHECK(gpio_set_direction(5, GPIO_MODE_OUTPUT)); // AMPLYFIER
//    ESP_ERROR_CHECK(gpio_set_direction(5, 1)); // AMPLYFIER
//}
//
//void beeep() {
//    int duration = 150;
//    int voltage = 255;
//    float  frequency = 0.8;
//    int delay = 2;
//
//    while (duration > 0) {
//        for (float i = 0; i < voltage; i+= frequency) {
//            dac_output_voltage(DAC_CHANNEL_1, i);
//            ets_delay_us(delay);
//        }
//        duration--;
//        ets_delay_us(10);
//    }
//    vTaskDelay(10);
//}
//
//
//
//
//void data_from_buttons(void *arg) {
//    t_app *apps = (t_app*)arg;
//    amplyfier_and_button_init();
//
//    t_button sw1 = (t_button){0, 1, 0};
//    t_button sw2 = (t_button){0, 1, 0};
//    _Bool was_pressed1 = 0;
//    _Bool was_pressed2 = 0;
//     while (1) {
//        sw1.turn_sw = gpio_get_level(SWP_1);
//        sw2.turn_sw = gpio_get_level(SWP_2);
////        switch_helper(&sw1);
////        switch_helper(&sw2);
//
//        }
//
//}
