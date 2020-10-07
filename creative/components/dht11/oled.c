#include "oled.h"
#include "dht11.h"
#include "font6x8.h"


//void oled_view(t_display *display) {
//
//
//
//}

static void AsciiStr_to_fontStr(char *str, t_display *display) {
    int font_str_intdex = ((SCREEN_WIDTH - strlen(str) * 6) / 2) + SCREEN_WIDTH * 3;
    int index_of_simbol = 0;

    for (int i = 0; i < strlen(str); i++) {
        index_of_simbol = (str[i] - 32) * 6;                    //first simbol from font6x8.h is the 32th of ascii table
        for (int j = 0; j < 6; j++) {                                               // every simbol in ascii is 6 byte
            display->font_str[font_str_intdex] = font6x8[index_of_simbol++];
            font_str_intdex++;
        }
    }
}


void write_to_oled(t_display *display, char *str) {
    AsciiStr_to_fontStr(str, display);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (display->addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x80, true); // single command
    i2c_master_write_byte(cmd, 0x00, true); 
    i2c_master_write_byte(cmd, 0x40, true); // data stream
    i2c_master_write(cmd, display->font_str, 128*8, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(display->port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

static void oled_update(t_display *display, char *str) {
    write_to_oled(display, str);
}

static void oled_clear(t_display *display) {
    memset(display->font_str, 0, SCREEN_SIZE);

}

static void init_i2c(void) {
    i2c_config_t i2c_config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = SDA_PIN,
            .scl_io_num = SCL_PIN,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = 1000000
    };
    i2c_param_config(I2C_PORT, &i2c_config);
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);
}

static void oled_initialization(t_display *display) {
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

// view

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

void data_to_oled(void *arg) {
    gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_32, 1);

    t_app *apps = (t_app*)arg;
    t_display *display = malloc(sizeof(t_display));
    display->addr = I2C_ADDR;
    display->port = I2C_PORT;
    init_i2c();
    oled_initialization(display);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    display->font_str = (uint8_t*)malloc(sizeof(uint8_t) * (128 * 8));
    bzero(display->font_str, SCREEN_SIZE);


    char t[17];
    char h[15];
//    printf("in oled %d   %d \n\n", apps->temp_hum[0], apps->temp_hum[1]);
    while (1) {
        sprintf(t, "Temperature: %dC", apps->temp_hum[0]);
        sprintf(h, "Humidity: %d%%", apps->temp_hum[1]);
        oled_clear(display);
        oled_update(display, h);
        write_to_oled(display, h);
        oled_update(display, h);
        vTaskDelay(2000/portTICK_PERIOD_MS); // todo chek delay
    }
}

