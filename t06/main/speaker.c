#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"                                                                                //gpio_num_t
#include "esp_err.h"
#include <driver/dac.h>

static void play(int duration, int voltage, float frequency, int delay) {
    while (duration > 0) {
        for (float i = 0; i < voltage; i+= frequency) {
            dac_output_voltage(DAC_CHANNEL_1, i);
            ets_delay_us(delay);
        }
        duration--;
        ets_delay_us(10);
    }
    vTaskDelay(10);
}

static void three_standard_measures() {
    play(750, 255, 0.8, 2);     // b_quarter_whith_dot
    play(250, 255, 0.8, 2);     // b_eighth
    play(250, 255, 0.8, 2);     // b_eighth
    play(200, 255, 0.71, 2);    // as_eighth
    play(250, 255, 0.8, 2);     // b_eighth
    play(250, 255, 0.85, 2);    // ces_eighth
    play(900, 254, 0.955, 2);    //des_quarter_whith_dot
    play(250, 255, 0.85, 2);    // ces_eighth
    play(450, 255, 0.8, 2);     // b_quarter
    play(400, 255, 0.71, 2);    // as_quarter
    play(350, 254, 0.63, 2);    // ges_quarter
    play(400, 255, 0.8, 2);     // b_quarter
    play(300, 254, 0.6, 2);     // fes_quarter
    play(400, 255, 0.8, 2);     // b_quarter

}
static void first_sentence() {
    three_standard_measures(); //+ the end of sentence
    play(450, 254, 0.62, 3);    // es_quarter_whith_dot
    play(150, 254, 0.6, 2);     // fes_eighth
    play(350, 254, 0.63, 2);    // ges_quarter
    play(400, 255, 0.71, 2);    // as_quarter

}

static void second_sentence() {
    three_standard_measures(); //+ the end of sentence
    play(1200, 254, 1.25, 3);    // es_half
    play(1200, 254, 1.25, 3);    // es_hal

// the second variant: an octave lowwer
//    play(550, 254, 0.61, 3);    // es_half
//    vTaskDelay(10);
//    play(550, 254, 0.61, 3);    // es_half
//    vTaskDelay(10);


}

void app_main() {
    dac_output_enable(DAC_CHANNEL_1);
    vTaskDelay(50);
    first_sentence();
    second_sentence();
}

