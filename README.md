# STM32 SSD1306 template

Project template for STM32 using SSD1306 compatible OLED display implemeted with libopenm3.

Hardware list:

* STM32F4 discovery debug board (STM32F407)
* SSD1306 128x64 OLED I2C display

# Display wiring:

~~~
PB6 --> SCL
PB7 --> SDA
VDD --> 3.3V
VSS --> GND
~~~

# Software dependencies

* Libopencm3 libraries https://github.com/libopencm3/libopencm3
* gcc-arm-none-eabi compiler
* OpenOCD utility for debug and flash

# Build instructions

Clone this repository and libopencm3 repository. Set the `LIBPATH` variable to the actual path to libopencm3 in `rules.mk` line 60.

Execute `make` to build the firmware. Then connect board to USB and execute `make flash` to flash the firmware.

