#include "hardware.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "nrf_gpio.h"

#include <stdbool.h>

#define TWI_ADDRESSES (127)

static volatile bool m_xfer_done = false;
static bool read_something = false;

#if TWI0_ENABLED
#define TWI_INSTANCE_ID 0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID 1
#endif

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

static void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch(p_event->type)
    {
        case NRF_DRV_TWI_EVT_ADDRESS_NACK:
        {
            m_xfer_done = true;
            break;
        }
        case NRF_DRV_TWI_EVT_DATA_NACK:
        {
            m_xfer_done = true;
            break;
        }
        case NRF_DRV_TWI_EVT_DONE:
        {
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                read_something = true;
            }
            m_xfer_done = true;
            break;
        }
        default:
        {
            m_xfer_done = false;
            break;
        }
    }
}

static void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_oled_config = {
       .scl                = PIN_I2C_SCL,
       .sda                = PIN_I2C_SDA,
       .frequency          = NRF_DRV_TWI_FREQ_400K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false,
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_oled_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

int main(void)
{
    nrf_gpio_cfg_output(PIN_LED_RED);
    nrf_gpio_cfg_output(PIN_LED_GREEN);
    nrf_gpio_cfg_output(PIN_LED_BLUE);

    nrf_gpio_pin_set(PIN_LED_RED);
    nrf_gpio_pin_set(PIN_LED_GREEN);
    nrf_gpio_pin_set(PIN_LED_BLUE);

    twi_init();

    for (uint8_t address = 0x00; address <= TWI_ADDRESSES; address++)
    {
        m_xfer_done = false;
        uint8_t sample = 0;
        ret_code_t err_code = nrf_drv_twi_rx(&m_twi, address, &sample, sizeof(sample));
        (void)err_code;
        while (!m_xfer_done)
        {
            __WFE();
        }
        if (read_something)
        {
            while (true)
            {
                nrf_gpio_pin_toggle(PIN_LED_GREEN);
                nrf_delay_ms(500);
            }
        }
    }

    while (true)
    {
        nrf_gpio_pin_toggle(PIN_LED_RED);
        nrf_delay_ms(500);
    }
}
