#include "driver/i2c.hpp"
#include "driver/oled.hpp"
#include "hardware.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

namespace
{
void init_logging()
{
    APP_ERROR_CHECK(NRF_LOG_INIT(nullptr));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

void init_leds()
{
    nrf_gpio_cfg_output(PIN_LED_RED);
    nrf_gpio_cfg_output(PIN_LED_GREEN);
    nrf_gpio_cfg_output(PIN_LED_BLUE);

    nrf_gpio_pin_set(PIN_LED_RED);
    nrf_gpio_pin_set(PIN_LED_GREEN);
    nrf_gpio_pin_set(PIN_LED_BLUE);
}
} // namespace

int main()
{
    init_logging();
    init_leds();

    i2c::init();
    oled::init();

    while (true)
    {
        oled::print_hello();
        nrf_delay_ms(10);
    }
}
