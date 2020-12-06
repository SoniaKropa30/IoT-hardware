#include "hardware_creative.h"

void data_from_buttons(void *arg) {
    t_app *apps = (t_app*)arg;
    amplyfier_and_button_init();

    _Bool sw1 = -1;
    _Bool sw2 = -1;
    _Bool was_pressed1 = 0;
    _Bool was_pressed2 = 0;
    while (1) {
        sw1 = gpio_get_level(SWP_1);
        sw2 = gpio_get_level(SWP_2);

        if(!sw1 && was_pressed1 == 0)
            was_pressed1 = 1;
        if(!sw1 && was_pressed1) {
            beeep();
            was_pressed1 = 0;
            apps->button1 = 1;
            apps->button2 = 0;
        }
        if(!sw2 && was_pressed2 == 0)
            was_pressed2 = 1;
        if(!sw2 && was_pressed2) {
            beeep();
            was_pressed2 = 0;
            apps->button1 = 0;
            apps->button2 = 1;
        }
        vTaskDelay(10/portTICK_PERIOD_MS); // todo chek delay
    }
}