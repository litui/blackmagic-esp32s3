set(SOURCES
    "main.c"
    "delay.c"
    "usb.c"
    "usb-uart.c"
    "led.c"
    "soft-uart-log.c"
    "display.c"
)

set (INCLUDES
    "."
    "graphics"
)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS ${INCLUDES})
