> Work in progress

### The hardware :

#### Borads supported:

The project supports 4 development boards :
* [**The nRF52-DK (PCA10040)**](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52-DK).
* [**The nRF52840-DK (PCA10056)**](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52840-DK).
* [**The Adafruit Feather nRF52 Bluefruit LE (ADA32)**](https://www.adafruit.com/product/3406).
* [**The Adafruit Feather nRF52840 Express (ADA40)**](https://www.adafruit.com/product/4062).

#### RGB led :

We're controlling a **WS2812b** RGB led, as it is one of Neopixels leds that supports volatges ranges from **3.3 to 5v**. So, no aditional components will be required to drive it with our **3.3v** based SOCs.
There are other Neopixels type like the **WS2812** RGB led, this type supports voltages ranges from **5v to 7v**, so you may need to use a logic level converter circuit to drive it.

### The firmware :

The project is :
* Compatible with nRF5_SDK versions starting from **v15.3**.
* Uses the **SEGGER** toolchain.
* Uses the **I2S** peripehral to drive the WS2812b RGB led.

If this is your first time working with the nRF5_SDK, i do recommend following my [**getting started guide**](https://nrf5dev.com/tutorials/getting-started/).

### Testing the application :

If you're using any of the Adafruit boards, make sure you head over to the [boards_files](https://github.com/rmptxf/NeoController/blob/master/boards_files) folder, and follow the included instruction.

If you will be testing on **the Adafruit Feather nRF52840 Express (ADA40)**, you already have an on-board WS2812b ready to use.

![The Adafruit Feather nRF52840 Express](https://github.com/rmptxf/NeoController/blob/master/assets/Adafruit_Feather_nRF52840_Express.PNG)

And it is already set in the firmware.

If not, you'll need to get a WS2812b RGB led module, like [**this one**](https://www.sparkfun.com/products/13282) from **Sparfun**.

![SparkFun RGB LED Breakout - WS2812B](https://github.com/rmptxf/NeoController/blob/master/assets/Ws2812B_PinsRev.jpg)

> Make sure you use the **DI** pin for connecting it to you board.