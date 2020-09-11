
/* Board file for the Adafruit Feather nRF52840 Express (ADA40)
 * According to : https://cdn-learn.adafruit.com/assets/assets/000/068/545/original/circuitpython_nRF52840_Schematic_REV-D.png
 * Product link : https://www.adafruit.com/product/4062
 * Author : Abdelali Boussetta @rmptxf
 */

#ifndef ADA40_H
#define ADA40_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

#define LEDS_NUMBER       2

#define LED_1             NRF_GPIO_PIN_MAP(1,10)  // blue led
#define LED_2             NRF_GPIO_PIN_MAP(1,15)  // red led

#define LED_START         LED_1
#define LED_STOP          LED_2

#define LEDS_ACTIVE_STATE 1

#define LEDS_LIST { LED_1, LED_2 }

#define LEDS_INV_MASK     LEDS_MASK

#define BSP_LED_0         LED_1
#define BSP_LED_1         LED_2

#define BUTTONS_NUMBER    1
#define BUTTON_DETECTION_TIME 50

// UserSW
#define BUTTON_1          NRF_GPIO_PIN_MAP(1,2) 
#define BUTTON_PULL       NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0     BUTTON_1

// NEOPIXEL
#define NEOPIXEL_PIN     NRF_GPIO_PIN_MAP(0,16)                  
#define NEOPIXELS_NUMBER 1

// UART
#define RX_PIN_NUMBER   NRF_GPIO_PIN_MAP(0,24)
#define TX_PIN_NUMBER   NRF_GPIO_PIN_MAP(0,25) 
#define HWFC           true

// QSPI
#define BSP_QSPI_SCK_PIN   NRF_GPIO_PIN_MAP(0,19)
#define BSP_QSPI_CSN_PIN   NRF_GPIO_PIN_MAP(0,20)
#define BSP_QSPI_IO0_PIN   NRF_GPIO_PIN_MAP(0,17)
#define BSP_QSPI_IO1_PIN   NRF_GPIO_PIN_MAP(0,22)
#define BSP_QSPI_IO2_PIN   NRF_GPIO_PIN_MAP(0,23)
#define BSP_QSPI_IO3_PIN   NRF_GPIO_PIN_MAP(0,21)

// I2C
#define SCL_PIN            NRF_GPIO_PIN_MAP(0,11) 
#define SDA_PIN            NRF_GPIO_PIN_MAP(0,12)  

// SPI
#define MOSI_PIN           NRF_GPIO_PIN_MAP(0,13)
#define MISO_PIN           NRF_GPIO_PIN_MAP(0,15)
#define SCK_PIN            NRF_GPIO_PIN_MAP(0,14)

// GPIO PINS
#define D5_PIN             NRF_GPIO_PIN_MAP(1,8)
#define D6_PIN             NRF_GPIO_PIN_MAP(0,7)
#define D9_PIN             NRF_GPIO_PIN_MAP(0,26)
#define D10_PIN            NRF_GPIO_PIN_MAP(0,27)
#define D11_PIN            NRF_GPIO_PIN_MAP(0,6)
#define D12_PIN            NRF_GPIO_PIN_MAP(0,8)
#define D13_PIN            NRF_GPIO_PIN_MAP(1,9)

// ANALOG PINS
#define A0_PIN             NRF_GPIO_PIN_MAP(0,4)
#define A1_PIN             NRF_GPIO_PIN_MAP(0,5)
#define A2_PIN             NRF_GPIO_PIN_MAP(0,30)
#define A3_PIN             NRF_GPIO_PIN_MAP(0,28)
#define A4_PIN             NRF_GPIO_PIN_MAP(0,2)
#define A5_PIN             NRF_GPIO_PIN_MAP(0,3)

#define A6_PIN             NRF_GPIO_PIN_MAP(0,29)
#define A7_PIN             NRF_GPIO_PIN_MAP(0,31)

#define AREF_PIN           A7_PIN

// Battery VDIV PIN
#define VDID_PIN           A6_PIN

// NFC
#define D2_PIN             NRF_GPIO_PIN_MAP(0,10)
#ifdef __cplusplus
}
#endif

#endif // ADA40_H
