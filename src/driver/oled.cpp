#include "oled.hpp"

#include "driver/i2c.hpp"
#include "hardware.h"
#include "nordic_common.h"
#include "nrf_delay.h"
#include "u8g2.h"
#include "u8x8.h"

#include <array>

constexpr size_t SEND_BUFFER_SIZE = 32;

namespace
{
u8g2_t u8g2;
std::array<uint8_t, SEND_BUFFER_SIZE> send_buffer = {0};
uint8_t send_buffer_index = 0;

uint8_t u8x8_msg_byte_callback(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_BYTE_SEND:
        {
            auto data = static_cast<const uint8_t *>(arg_ptr);
            while (arg_int > 0)
            {
                send_buffer[send_buffer_index] = *data;
                send_buffer_index++;
                data++;
                arg_int--;
            }
            break;
        }
        case U8X8_MSG_BYTE_START_TRANSFER:
            send_buffer_index = 0;
            break;
        case U8X8_MSG_BYTE_END_TRANSFER:
            i2c::transfer_blocking(u8x8_GetI2CAddress(u8x8), send_buffer.data(), send_buffer_index);
            break;
        default:
            return 0;
    }
    return 1;
}

uint8_t u8x8_msg_gpio_and_delay_callback(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    UNUSED_PARAMETER(arg_ptr);
    switch (msg)
    {
        case U8X8_MSG_DELAY_MILLI:
            nrf_delay_ms(arg_int);
            break;

        case U8X8_MSG_DELAY_10MICRO:
            nrf_delay_us(10 * arg_int);
            break;

        default:
            u8x8_SetGPIOResult(u8x8, 1); // default return value
            break;
    }
    return 1;
}
} // namespace

void oled::init()
{
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2,
                                           U8G2_R0,
                                           static_cast<u8x8_msg_cb>(u8x8_msg_byte_callback),
                                           static_cast<u8x8_msg_cb>(u8x8_msg_gpio_and_delay_callback));

    u8g2_SetI2CAddress(&u8g2, TWI_ADDRESS_OLED);

    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
}

void oled::print_hello()
{
    static u8g2_uint_t x = 30;
    static u8g2_uint_t y = 30;

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
    x = (x + 1) % 20;
    y = (y + 1) % 20;
    u8g2_DrawStr(&u8g2, y, x, "Hello World!");
    u8g2_SendBuffer(&u8g2);
}
