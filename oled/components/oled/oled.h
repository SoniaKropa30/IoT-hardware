#ifndef OLED_H
#define OLED_H

#define SDA_PIN  GPIO_NUM_21
#define SCL_PIN  GPIO_NUM_22
#define I2C_ADDR 0x3C
#define I2C_PORT I2C_NUM_0
#define SCREEN_WIDTH 128
#define PAGE_COUNT 8
#define SCREEN_SIZE 1024 // width * number of pages

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2c.h"
#include <strings.h>
#include <string.h>


typedef struct {
    uint8_t addr;           // I2C address
    i2c_port_t port;        // I2C interface port
    uint16_t changes;       // page change bit to optimize writes
    uint8_t pages[16][128]; // page buffer
} sh1106_t;

void oled_init(sh1106_t *display);
void write_to_oled(sh1106_t *display);
void oled_update(sh1106_t *display);
void oled_clear(sh1106_t *display);
#endif
