#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include <driver/dac.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <driver/uart.h>


void app_main() {
    const int uart_buffer_size = 1024;
    int uart_num = UART_NUM_2;
    uart_config_t uart_config = {
            .baud_rate = 9600,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 17, 16, UART_PIN_NO_CHANGE , UART_PIN_NO_CHANGE));
    QueueHandle_t uart_queue;
    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size,
                                        uart_buffer_size, 10, &uart_queue, 0));
    const char *test_str = "\e[41mRED\x1b[0m \e[42mGREEN\x1b[0m \e[44mBLUE\x1b[0m \e[49mDEFAUL\x1b[0m\n";
    if(uart_write_bytes_with_break(uart_num, test_str, strlen(test_str), 104) == -1)
        write(2, "ERROR WRITING BITS\n", 19);
    ESP_ERROR_CHECK(uart_wait_tx_done(uart_num, 100));
}

