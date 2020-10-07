#include "pwm_dac.h"

void app_main() {
    ledc_timer_config_t ledc_timer;
    ledc_channel_config_t ledc_channel;
    init_timer_chanel(&ledc_timer, &ledc_channel);
    dac_output_enable(DAC_CHANNEL_2);

    while (1) {
        PWM_method(&ledc_channel);
        DAC_method();
    }
}

