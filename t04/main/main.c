#include "dht11.h"

static void read_data_error(char * level, char *exp) {
    write(2, "ERROR from function READ_DATA: ", 31);
    write(2, level, strlen(level));
    write(2, " expected ", 34);
    write(2, exp, strlen(exp));
    write(2, "\n", 1);
}

void app_main() {
    int result = 2;
    int i = 0;

    sensor_activation();
    uint8_t *bin_nbr = (uint8_t*)malloc(sizeof(uint8_t)  * 5);
    if(!bin_nbr)
        write(2, "memory allocation error from bin_nbr\n", 38);
    bzero(bin_nbr, sizeof(*bin_nbr));

    if((result = read_data(80, 0)) == -1)
        read_data_error("level_1","0");
    if((result = read_data(80, 1)) == -1)
        read_data_error("level_2","1");
    while (i < 40) {
        if ((result = read_data(50, 0)) == -1)
            read_data_error("level_3","0");
        if ((result = read_data(70, 1)) == -1)
            read_data_error("level_4","1/0");
        bin_nbr[i / 8] <<= 1; // ont the first iteration all bits will be 0;
        if (result > 28)
            bin_nbr[i / 8] += 1;
        i++;
    }
    check_sum(bin_nbr);
}

