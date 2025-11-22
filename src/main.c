#include "hardware.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"

#include <stdbool.h>

int main(void)
{
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_2);
    nrf_gpio_cfg_output(LED_3);

    while (true)
    {
        nrf_gpio_pin_toggle(LED_1);
        nrf_delay_ms(500);
        nrf_gpio_pin_toggle(LED_2);
        nrf_delay_ms(500);
        nrf_gpio_pin_toggle(LED_3);
        nrf_delay_ms(500);
    }
}
