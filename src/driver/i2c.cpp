#include "i2c.hpp"

#include "hardware.h"
#include "nrf_drv_twi.h"

#if TWI0_ENABLED
#define TWI_INSTANCE_ID 0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID 1
#endif

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

static volatile bool m_xfer_done = false;
static bool read_something = false;

namespace
{
void twi_handler(nrf_drv_twi_evt_t const *p_event, void *p_context)
{
    UNUSED_PARAMETER(p_context);
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_ADDRESS_NACK:
        case NRF_DRV_TWI_EVT_DATA_NACK:
            m_xfer_done = true;
            break;
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                read_something = true;
            }
            m_xfer_done = true;
            break;
        default:
            m_xfer_done = false;
            break;
    }
}
} // namespace

void i2c::init()
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_oled_config = {
        .scl = PIN_I2C_SCL,
        .sda = PIN_I2C_SDA,
        .frequency = NRF_DRV_TWI_FREQ_400K,
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
        .clear_bus_init = false,
        .hold_bus_uninit = false,
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_oled_config, twi_handler, nullptr);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

void i2c::transfer_blocking(std::uint8_t address, std::uint8_t *data, std::size_t length)
{
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, address, data, length, false);
    APP_ERROR_CHECK(err_code);
    while (!m_xfer_done)
    {
        __WFE();
    }
}
