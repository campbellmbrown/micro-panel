/**
 * Hardware configuration for Seeed XIAO BLE Sense board.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

#define LEDS_ACTIVE_STATE 0

#define PIN_LED_RED   (NRF_GPIO_PIN_MAP(0, 26))
#define PIN_LED_GREEN (NRF_GPIO_PIN_MAP(0, 30))
#define PIN_LED_BLUE  (NRF_GPIO_PIN_MAP(0, 6))

#define PIN_I2C_SCL    (NRF_GPIO_PIN_MAP(0, 5))
#define PIN_I2C_SDA    (NRF_GPIO_PIN_MAP(0, 4))

#ifdef __cplusplus
}
#endif
