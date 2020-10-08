#include "dht11.h"


void dht11_initialization(void) {
    gpio_set_direction(GPIO_POWER, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_DATA, GPIO_MODE_OUTPUT);
    ESP_ERROR_CHECK(gpio_set_level(GPIO_POWER, 1));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_DATA, 1));
    ets_delay_us(2000010);
}

static void read_data_error(char * level, char *exp) {
    write(2, "ERROR from function READ_DATA: ", 31);
    write(2, level, strlen(level));
    write(2, " expected ", 34);
    write(2, exp, strlen(exp));
    write(2, "\n", 1);
}

static int read_data(int time, int mode) {
    int count = 0;
    while (gpio_get_level(GPIO_DATA) == mode) {
        if (count > time)
            return -1;
        ets_delay_us(1);
        count++;
    }
    if (count == 0)
        return -1;
    return count;
}

void sensor_activation(void) {
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_DATA, GPIO_MODE_OUTPUT)); //for print
    ESP_ERROR_CHECK(gpio_set_level(GPIO_DATA, 1));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_DATA, 0));
    ets_delay_us(18000);
    ESP_ERROR_CHECK(gpio_set_level(GPIO_DATA, 1));
    ets_delay_us(30);
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_DATA, GPIO_MODE_INPUT)); // todo was checked
    if((read_data(80, 0)) == -1)
        read_data_error("level_1","0");
    if((read_data(80, 1)) == -1)
        read_data_error("level_2","1");
}

static int check_sum (uint8_t *bin_nbr) {
    if ((bin_nbr[0] + bin_nbr[1] + bin_nbr[2] + bin_nbr[3]) != bin_nbr[4]) {
        return -1;
    }
    else
        return 0;

}

int take_data_from_dht11(int *temp_hum) {
    int result = 2;
    int i = 0;

    uint8_t bin_nbr[5];
    bzero(&bin_nbr, (sizeof(uint8_t) * 5));

    while (i < 40) {
        if ((read_data(50, 0)) == -1)
            read_data_error("level_3","0");
        if ((result = read_data(70, 1)) == -1)
            read_data_error("level_4","1/0");
        bin_nbr[i / 8] <<= 1; // ont the first iteration all bits will be 0;
        if (result > 28)
            bin_nbr[i / 8] += 1;
        i++;
    }
    if(check_sum(bin_nbr) == -1) {
        return -1;
    }
    else {
        temp_hum[0] = bin_nbr[2];
        temp_hum[1] = bin_nbr[0];
        return 0;
    }

}
