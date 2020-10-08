idf_component_register(SRCS "main.c"
                        SRCS "dht_task.c"
                        SRCS "oled_task.c"
                        SRCS "accelerometer_task.c"
                        INCLUDE_DIRS "."
#                        REQUIRES buttons
                        REQUIRES dht11
                        REQUIRES oled
                        REQUIRES accelerometer
        )