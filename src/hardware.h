/**
 * Hardware configuration for Seeed XIAO BLE Sense board.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define LEDS_NUMBER 3

#define LEDS_ACTIVE_STATE 0

#define LED_1 (26)
#define LED_2 (30)
#define LED_3 (6)

#define LEDS_LIST {LED_1, LED_2, LED_3}

#ifdef __cplusplus
}
#endif
