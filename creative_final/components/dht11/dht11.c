#include "dht11.h"



static void read_data_error(char * level, char *exp) {
    write(2, "ERROR from function READ_DATA: ", 31);
    write(2, level, strlen(level));
    write(2, " expected ", 34);
    write(2, exp, strlen(exp));
    write(2, "\n", 1);
}

int read_data(int time, int mode) {
//    int count = 0;
//    int i = 0;
//    _Bool before_mode = 0;
//
//    while (i < time) {
//        if((gpio_get_level(GPIO_DATA) != mode) && !before_mode) {
////            i++;
////            ets_delay_us(1);
//            continue;
//        }
//        if (gpio_get_level(GPIO_DATA) == mode) {
//            before_mode = 1;
//            count++;
//        }
//        else {
//           break;
//        }
//
//        ets_delay_us(1);
//        i++;
//    }
//    if (count == 0)
//        return -1;
//    return count; c 

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
    gpio_set_direction(GPIO_DATA, GPIO_MODE_OUTPUT); //for print
    gpio_set_level(GPIO_DATA, 0);
    ets_delay_us(18000);
    gpio_set_level(GPIO_DATA, 1);
    ets_delay_us(40);
//    gpio_set_direction(GPIO_DATA, GPIO_MODE_INPUT); //for print
}

void check_sum (uint8_t *bin_nbr, t_app *app) {
    if ((bin_nbr[0] + bin_nbr[1] + bin_nbr[2] + bin_nbr[3]) != bin_nbr[4])
        write(2, "ERROR FROM CHECK_SUM\n", 21);
    else {
        app->temp_hum[0] = bin_nbr[2]; // temperature
        app->temp_hum[1] = bin_nbr[0]; // humidity
    }
}

static void data_reception(t_app *app) {
    int result = 2;
    int i = 0;

    uint8_t bin_nbr[5];
    bzero(&bin_nbr, (sizeof(uint8_t) * 5));

    if((read_data(80, 0)) == -1)
        read_data_error("level_1","0");
    if((read_data(80, 1)) == -1)
        read_data_error("level_2","1");
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
    for(int k = 0; k < 5; k++)
        printf("%d", bin_nbr[k]);
    printf("\n");
    check_sum(bin_nbr, app);
//    free(bin_nbr);
//    printf("temp = %d\n\n", apps->temp);


}



void data_from_dht11(void *arg) {
    t_app *app = (t_app*)arg;

    while(1) {
        sensor_activation();
        data_reception(app);
//        printf("in dht %d  %d\n\n", app->temp_hum[0], app->temp_hum[1]);

        vTaskDelay(2000);
    }
}
