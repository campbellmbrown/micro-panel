set(U8G2_SOURCES
    u8g2/csrc/u8x8_display.c
    u8g2/csrc/u8g2_font.c
    u8g2/csrc/u8x8_8x8.c
    u8g2/csrc/u8g2_hvline.c
    u8g2/csrc/u8g2_intersection.c
    u8g2/csrc/u8g2_fonts.c
    u8g2/csrc/u8g2_setup.c
    u8g2/csrc/u8g2_buffer.c
    u8g2/csrc/u8g2_d_setup.c
    u8g2/csrc/u8g2_ll_hvline.c
    u8g2/csrc/u8x8_d_ssd1306_128x64_noname.c
    u8g2/csrc/u8x8_cad.c
    u8g2/csrc/u8x8_byte.c
    u8g2/csrc/u8x8_gpio.c
    u8g2/csrc/u8g2_d_memory.c
    u8g2/csrc/u8x8_setup.c
)

set(U8G2_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/u8g2/csrc
)

add_library(u8g2 STATIC ${U8G2_SOURCES})
target_include_directories(u8g2 PUBLIC ${U8G2_INCLUDES})

set(NRF5_SDK_SOURCES
    nrf5_sdk/modules/nrfx/mdk/gcc_startup_nrf52840.S
    nrf5_sdk/components/libraries/log/src/nrf_log_frontend.c
    nrf5_sdk/components/libraries/log/src/nrf_log_str_formatter.c
    nrf5_sdk/components/libraries/util/app_error.c
    nrf5_sdk/components/libraries/util/app_error_handler_gcc.c
    nrf5_sdk/components/libraries/util/app_error_weak.c
    nrf5_sdk/components/libraries/util/app_util_platform.c
    nrf5_sdk/components/libraries/util/nrf_assert.c
    nrf5_sdk/components/libraries/atomic/nrf_atomic.c
    nrf5_sdk/components/libraries/balloc/nrf_balloc.c
    nrf5_sdk/external/fprintf/nrf_fprintf.c
    nrf5_sdk/external/fprintf/nrf_fprintf_format.c
    nrf5_sdk/components/libraries/memobj/nrf_memobj.c
    nrf5_sdk/components/libraries/ringbuf/nrf_ringbuf.c
    nrf5_sdk/components/libraries/strerror/nrf_strerror.c
    nrf5_sdk/modules/nrfx/soc/nrfx_atomic.c
    nrf5_sdk/modules/nrfx/mdk/system_nrf52840.c
    nrf5_sdk/modules/nrfx/drivers/src/nrfx_twim.c
    nrf5_sdk/integration/nrfx/legacy/nrf_drv_twi.c
    nrf5_sdk/modules/nrfx/drivers/src/prs/nrfx_prs.c
    nrf5_sdk/components/libraries/log/src/nrf_log_default_backends.c
    nrf5_sdk/components/libraries/log/src/nrf_log_backend_uart.c
    nrf5_sdk/integration/nrfx/legacy/nrf_drv_uart.c
    nrf5_sdk/modules/nrfx/drivers/src/nrfx_uarte.c
    nrf5_sdk/modules/nrfx/drivers/src/nrfx_uart.c
    nrf5_sdk/components/libraries/log/src/nrf_log_backend_serial.c
)

set(NRF5_SDK_INCLUDES
    nrf5_sdk/components
    nrf5_sdk/modules/nrfx/mdk
    nrf5_sdk/components/libraries/strerror
    nrf5_sdk/components/toolchain/cmsis/include
    nrf5_sdk/components/libraries/util
    nrf5_sdk/components/libraries/balloc
    nrf5_sdk/components/libraries/ringbuf
    nrf5_sdk/modules/nrfx/hal
    nrf5_sdk/components/libraries/bsp
    nrf5_sdk/components/libraries/log
    nrf5_sdk/modules/nrfx
    nrf5_sdk/components/libraries/experimental_section_vars
    nrf5_sdk/components/libraries/delay
    nrf5_sdk/integration/nrfx
    nrf5_sdk/components/drivers_nrf/nrf_soc_nosd
    nrf5_sdk/components/libraries/atomic
    nrf5_sdk/components/boards
    nrf5_sdk/components/libraries/memobj
    nrf5_sdk/external/fprintf
    nrf5_sdk/components/libraries/log/src
    nrf5_sdk/integration/nrfx/legacy
    nrf5_sdk/modules/nrfx/drivers/include
)

add_library(nrf5_sdk STATIC ${NRF5_SDK_SOURCES})
target_include_directories(nrf5_sdk PUBLIC ${NRF5_SDK_INCLUDES})

# Set system include directories to suppress warnings from SDK code
set_target_properties(nrf5_sdk PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "$<TARGET_PROPERTY:nrf5_sdk,INTERFACE_INCLUDE_DIRECTORIES>"
)

target_compile_definitions(nrf5_sdk PUBLIC
    BOARD_CUSTOM
    BSP_DEFINES_ONLY
    CONFIG_GPIO_AS_PINRESET
    FLOAT_ABI_HARD
    NRF52840_XXAA
    __HEAP_SIZE=8192
    __STACK_SIZE=8192
)
