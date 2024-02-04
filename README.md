## ESP32S3 Blackmagic (Work-in-progress)

This is a "port" (loosely defined) of the [Blackmagic debugger](https://github.com/blackmagic-debug/blackmagic) to ESP32-S3, based on the work of the Flipper Devices team on [their ESP32-S2 version](https://github.com/flipperdevices/blackmagic-esp32-s2).

I wanted to rework this for ESP-IDF 5, the latest upstream Blackmagic changes, re-add JTAG support, and use the LilyGo T-Display S3 AMOLED since I have a couple of those boards around and want to eventually use the display. To this end, I started from scratch with a new tree and only pulled in the pieces that made sense, tweaking and fixing as I went.

### What's working

* The gdb server seems to be working fine, discovering over SWD, and able to do things

### What's not tested or not working

* JTAG (wasn't set up in the Flipper Zero version)
* Networking / wifi
    * these changed quite a bit in ESP-IDF 5 so I haven't brought them back yet
    * I don't really like aspects of how the original web interface was done -- wifi password shouldn't be so easily viewable/accessible, even from within the LAN
* NV storage (I didn't pull this in since it depends on having a configuration interface, which I don't yet)
* Flipper Zero CLI - I won't be importing this since I'm not using this debugger with the Flipper Zero
* CMSIS-DAP support - Might bring this back once I get the display working so it's easy to distinguish what state it's in
* (Not tested) serial monitoring on the second USB-CDC device
* (Not tested) blackmagic debug messages when enabled
* (Not tested) semihosting messages
* (Not tested) RTT messages

### Future to-do

* Support for that fancy little AMOLED display
    * Since we only have one (green) LED, it'd be nice to have virtual LEDs visible on the display for the other two
* Something for the buttons on the front to do
* More close alignment with how native Blackmagic works, especially in CDC paths on OSX (/dev/cu.usbmodem########, etc.)

### Building / Hardware considerations

This build takes up a fair bit of RAM so make sure if you're building for different hardware that your device has SPIRAM and that you have it configured and working in your sdkconfig.h (via menuconfig). You want to be able to use `CONFIG_SPIRAM_TRY_ALLOCATE_WIFI_LWIP=y` and `CONFIG_SPIRAM_ALLOW_BSS_SEG_EXTERNAL_MEMORY=y` at least. I made my SPIRAM accessible through malloc though the flipper devices version used `CONFIG_SPIRAM_USE_CAPS_ALLOC`.

An adjustment was made to the `CMakeLists.txt` for blackmagic-fw to ensure its core is compiled with `-std=c11`.