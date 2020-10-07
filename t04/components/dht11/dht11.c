#include "dht11.h"

int read_data(int time, int mode) {
    int count = 0;
    int i = 0;
    _Bool before_mode = 0;

    while (i < time) {
        if(gpio_get_level(GPIO_DATA) != mode && !before_mode)
            continue;
        else if (gpio_get_level(GPIO_DATA) == mode) {
            before_mode = 1;
            count++;
        }
        else
            break;
        ets_delay_us(1);
        i++;
    }
    if (count == 0)
        return -1;
    return count;
}

void sensor_activation(void) {
    gpio_set_direction(GPIO_POWER, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_DATA, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_POWER, 1);
    gpio_set_level(GPIO_DATA, 1);
    ets_delay_us(3000000);

    gpio_set_level(GPIO_DATA, 0);
    ets_delay_us(18000);

    gpio_set_level(GPIO_DATA, 1);
    ets_delay_us(40);

    gpio_set_direction(GPIO_DATA, GPIO_MODE_INPUT); //for print
}

void check_sum (uint8_t *bin_nbr) {
    if ((bin_nbr[0] + bin_nbr[1] + bin_nbr[2] + bin_nbr[3]) != bin_nbr[4])
        write(2, "ERROR FROM CHECK_SUM\n", 21);
    else
        printf("Temperature: %d C^M\nHumidity: %d %%^M\n",bin_nbr[2], bin_nbr[0]);
    free(bin_nbr);
    gpio_set_level(GPIO_POWER, 0);
    gpio_set_level(GPIO_DATA, 0);
}
