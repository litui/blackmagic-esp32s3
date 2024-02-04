set(SOURCES
    "main.c"
    "delay.c"
    "usb.c"
    "usb-uart.c"
    "led.c"
    "soft-uart-log.c"
)

set (INCLUDES
    "."
)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS ${INCLUDES}
                    REQUIRES blackmagic simple-uart tinyusb driver soft-uart)
