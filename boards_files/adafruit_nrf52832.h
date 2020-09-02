
/* Board file for the Adafruit Feather nRF52 Bluefruit LE - nRF52832 (ADA32)
 * According to : https://cdn-learn.adafruit.com/assets/assets/000/052/793/original/microcontrollers_revgsch.png
 * Product link : https://www.adafruit.com/product/3406
 * Author : Abdelali Boussetta @rmptxf
 */

#ifndef ADA32_H
#define ADA32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

#define LEDS_NUMBER       2

#define LED_1             NRF_GPIO_PIN_MAP(0,19)  // blue led
#define LED_2             NRF_GPIO_PIN_MAP(0,17)  // red led

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
#define BUTTON_1          NRF_GPIO_PIN_MAP(1,16) // Vertual button on D13
#define BUTTON_PULL       NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0     BUTTON_1

// UART
#define RX_PIN_NUMBER   NRF_GPIO_PIN_MAP(0,8)
#define TX_PIN_NUMBER   NRF_GPIO_PIN_MAP(0,6) 
#define HWFC            true

#define NOT_USED_PIN1   NRF_GPIO_PIN_MAP(0,23)   
#define NOT_USED_PIN2   NRF_GPIO_PIN_MAP(0,24) 

// I2C
#define SCL_PIN            NRF_GPIO_PIN_MAP(0,26) 
#define SDA_PIN            NRF_GPIO_PIN_MAP(0,25)  

// SPI
#define MOSI_PIN           NRF_GPIO_PIN_MAP(0,13)
#define MISO_PIN           NRF_GPIO_PIN_MAP(0,14)
#define SCK_PIN            NRF_GPIO_PIN_MAP(0,12)

// GPIO PINS
#define D5_PIN             NRF_GPIO_PIN_MAP(0,27)
#define D6_PIN             NRF_GPIO_PIN_MAP(0,30)
#define D9_PIN             NRF_GPIO_PIN_MAP(0,31)
#define D10_PIN            NRF_GPIO_PIN_MAP(0,11)
#define D11_PIN            NRF_GPIO_PIN_MAP(0,7)
#define D12_PIN            NRF_GPIO_PIN_MAP(0,15)
#define D13_PIN            NRF_GPIO_PIN_MAP(1,16)

// ANALOG PINS
#define A0_PIN             NRF_GPIO_PIN_MAP(0,2)
#define A1_PIN             NRF_GPIO_PIN_MAP(0,3)
#define A2_PIN             NRF_GPIO_PIN_MAP(0,4)
#define A3_PIN             NRF_GPIO_PIN_MAP(0,5)
#define A4_PIN             NRF_GPIO_PIN_MAP(0,28)
#define A5_PIN             NRF_GPIO_PIN_MAP(0,29)

#define A6_PIN             D6_PIN
#define A7_PIN             D6_PIN

// Battery VDIV PIN
#define VDID_PIN           NRF_GPIO_PIN_MAP(0,29)

// NFC
#define D1_PIN             NRF_GPIO_PIN_MAP(0,9)
#define D2_PIN             NRF_GPIO_PIN_MAP(0,10)

#ifdef __cplusplus
}
#endif

#endif // ADA32_H
