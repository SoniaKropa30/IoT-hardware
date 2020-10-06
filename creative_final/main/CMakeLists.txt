idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES buttons
                    REQUIRES dht11)
#                    REQUIRES oled
#                    REQUIRES accelerometer)