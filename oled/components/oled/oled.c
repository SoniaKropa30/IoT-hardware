#include "oled.h"
#include "font6x8.h"


void oled_init(sh1106_t *display) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (display->addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x0, true); // command stream
    i2c_master_write_byte(cmd, 0xAE, true); // off
    i2c_master_write_byte(cmd, 0xD5, true); // clock div
    i2c_master_write_byte(cmd, 0x80, true);
    i2c_master_write_byte(cmd, 0xA8, true); // multiplex
    i2c_master_write_byte(cmd, 0xFF, true);
    i2c_master_write_byte(cmd, 0x8D, true); // charge pump
    i2c_master_write_byte(cmd, 0x14, true);

    i2c_master_write_byte(cmd, 0x20, true); // for horizontal view
    i2c_master_write_byte(cmd, 0x00, true);

    i2c_master_write_byte(cmd, 0x10, true); // high column
    i2c_master_write_byte(cmd, 0xB0, true);
    i2c_master_write_byte(cmd, 0xC8, true);
    i2c_master_write_byte(cmd, 0x0, true); // low column
    i2c_master_write_byte(cmd, 0x10, true);
    i2c_master_write_byte(cmd, 0x40, true);
    i2c_master_write_byte(cmd, 0xA1, true); // segment remap
    i2c_master_write_byte(cmd, 0xA6, true);
    i2c_master_write_byte(cmd, 0x81, true); // contrast
    i2c_master_write_byte(cmd, 0xFF, true);
    i2c_master_write_byte(cmd, 0xAF, true); // on
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(display->port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

static void AsciiStr_to_fontStr(char *str, uint8_t *font_str) {
    int font_str_intdex = ((SCREEN_WIDTH - strlen(str) * 6) / 2) + SCREEN_WIDTH * 3;
    int index_of_simbol = 0;

    for (int i = 0; i < strlen(str); i++) {
        index_of_simbol = (str[i] - 32) * 6;                    //first simbol from font6x8.h is the 32th of ascii table
        for (int j = 0; j < 6; j++) {                                               // every simbol in ascii is 6 byte
            font_str[font_str_intdex] = font6x8[index_of_simbol++];
            font_str_intdex++;
        }
    }
}


void write_to_oled(sh1106_t *display) {
    uint8_t *font_str = (uint8_t*)malloc(sizeof(uint8_t) * (128 * 8));
    bzero(font_str, 128*8);
    AsciiStr_to_fontStr("Hello, World!", font_str);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (display->addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x80, true); // single command
    i2c_master_write_byte(cmd, 0x00, true); 
    i2c_master_write_byte(cmd, 0x40, true); // data stream
    i2c_master_write(cmd, font_str, 128*8, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(display->port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

void oled_update(sh1106_t *display) {
    for (uint8_t i = 0; i < 8; i++) {
        if (display->changes & (1 << i)) {
            write_to_oled(display);
        }
    }
}

void oled_clear(sh1106_t *display) {
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 128; j++) {
            display->pages[i][j] = 0x00;
        }
    }
}

