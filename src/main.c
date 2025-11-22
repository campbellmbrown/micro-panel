#include "hardware.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "u8g2.h"
#include "u8x8.h"

#include <stdbool.h>

#define TWI_ADDRESSES (127)

static volatile bool m_xfer_done = false;
static bool read_something = false;
static u8g2_t u8g2;

#if TWI0_ENABLED
#define TWI_INSTANCE_ID 0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID 1
#endif

#define OLED_ADDR 0x3C

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

static uint8_t u8g2_nrf_gpio_and_delay_twi_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch(msg)
    {
        case U8X8_MSG_DELAY_MILLI:
            // NRF_LOG_INFO("nrf_delay_ms(%d)", arg_int);
            nrf_delay_ms(arg_int);
            break;

        case U8X8_MSG_DELAY_10MICRO:
            // NRF_LOG_INFO("nrf_delay_us(%d)", 10*arg_int);
            nrf_delay_us(10*arg_int);
            break;

        default:
            u8x8_SetGPIOResult(u8x8, 1); // default return value
            break;
    }
    return 1;
}

static uint8_t u8x8_HW_com_twi_nrf52832(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    uint8_t *data;
    ret_code_t err_code;
    static uint8_t buffer[32];
    static uint8_t buf_idx;
    switch(msg)
    {
      case U8X8_MSG_BYTE_SEND:
      {
            data = (uint8_t *)arg_ptr;
            while( arg_int > 0 )
            {
              buffer[buf_idx++] = *data;
              data++;
              arg_int--;
            }
            break;
      }
      case U8X8_MSG_BYTE_START_TRANSFER:
      {
            buf_idx = 0;
            m_xfer_done = false;
            break;
      }
      case U8X8_MSG_BYTE_END_TRANSFER:
      {
            uint8_t addr = u8x8_GetI2CAddress(u8x8);
            (void)addr;

            err_code = nrf_drv_twi_tx(&m_twi, u8x8_GetI2CAddress(u8x8) , buffer, buf_idx, false);
            APP_ERROR_CHECK(err_code);
            while (!m_xfer_done)
            {
                __WFE();
            }
            break;
      }
      default:
            return 0;
    }
    return 1;
}

static void print_hello()
{
static int x = 30;
static int y= 30;

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
    x++;
    y++;
    x = (x % 20);
    y = (y % 20);
    u8g2_DrawStr(&u8g2, y, x, "Hello World!");
    u8g2_SendBuffer(&u8g2);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

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
            NRF_LOG_INFO("TWI device detected at address 0x%x: Read value 0x%02x", address, sample);
            break;
        }
    }

    if (!read_something)
    {
        while (true)
        {
            nrf_gpio_pin_toggle(PIN_LED_RED);
            nrf_delay_ms(500);
        }
    }

    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_HW_com_twi_nrf52832, u8g2_nrf_gpio_and_delay_twi_cb);
    u8g2_SetI2CAddress(&u8g2, OLED_ADDR);

    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2,0);

    while (true)
    {
        print_hello();
        nrf_delay_ms(10);
    }
}
