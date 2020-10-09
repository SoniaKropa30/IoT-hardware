idf_component_register(SRCS "main.c"
                        SRCS "task_dht.c"
                        SRCS "task_oled.c"
                        SRCS "task_buttons.c"
                        SRCS "task_accelerometer.c"
                        INCLUDE_DIRS "."
                        REQUIRES buttons
                        REQUIRES dht11
                        REQUIRES oled
                        REQUIRES accelerometer
        )