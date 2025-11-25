set(NRF_SDK_ROOT ${CMAKE_CURRENT_LIST_DIR}/nrf5_sdk)
set(U8G2_ROOT ${CMAKE_CURRENT_LIST_DIR}/u8g2)

set(U8G2_SOURCES
    ${U8G2_ROOT}/csrc/u8x8_display.c
    ${U8G2_ROOT}/csrc/u8g2_font.c
    ${U8G2_ROOT}/csrc/u8x8_8x8.c
    ${U8G2_ROOT}/csrc/u8g2_hvline.c
    ${U8G2_ROOT}/csrc/u8g2_intersection.c
    ${U8G2_ROOT}/csrc/u8g2_fonts.c
    ${U8G2_ROOT}/csrc/u8g2_setup.c
    ${U8G2_ROOT}/csrc/u8g2_buffer.c
    ${U8G2_ROOT}/csrc/u8g2_d_setup.c
    ${U8G2_ROOT}/csrc/u8g2_ll_hvline.c
    ${U8G2_ROOT}/csrc/u8x8_d_ssd1306_128x64_noname.c
    ${U8G2_ROOT}/csrc/u8x8_cad.c
    ${U8G2_ROOT}/csrc/u8x8_byte.c
    ${U8G2_ROOT}/csrc/u8x8_gpio.c
    ${U8G2_ROOT}/csrc/u8g2_d_memory.c
    ${U8G2_ROOT}/csrc/u8x8_setup.c
)

set(U8G2_INCLUDES
    ${U8G2_ROOT}/csrc
)

set(NRF5_SDK_SOURCES
    ${NRF_SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${NRF_SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
    ${NRF_SDK_ROOT}/components/libraries/log/src/nrf_log_str_formatter.c
    ${NRF_SDK_ROOT}/components/libraries/util/app_error.c
    ${NRF_SDK_ROOT}/components/libraries/util/app_error_handler_gcc.c
    ${NRF_SDK_ROOT}/components/libraries/util/app_error_weak.c
    ${NRF_SDK_ROOT}/components/libraries/util/app_util_platform.c
    ${NRF_SDK_ROOT}/components/libraries/util/nrf_assert.c
    ${NRF_SDK_ROOT}/components/libraries/atomic/nrf_atomic.c
    ${NRF_SDK_ROOT}/components/libraries/balloc/nrf_balloc.c
    ${NRF_SDK_ROOT}/external/fprintf/nrf_fprintf.c
    ${NRF_SDK_ROOT}/external/fprintf/nrf_fprintf_format.c
    ${NRF_SDK_ROOT}/components/libraries/memobj/nrf_memobj.c
    ${NRF_SDK_ROOT}/components/libraries/ringbuf/nrf_ringbuf.c
    ${NRF_SDK_ROOT}/components/libraries/strerror/nrf_strerror.c
    ${NRF_SDK_ROOT}/modules/nrfx/soc/nrfx_atomic.c
    ${NRF_SDK_ROOT}/modules/nrfx/mdk/system_nrf52840.c
    ${NRF_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_twim.c
    ${NRF_SDK_ROOT}/integration/nrfx/legacy/nrf_drv_twi.c
    ${NRF_SDK_ROOT}/modules/nrfx/drivers/src/prs/nrfx_prs.c
    ${NRF_SDK_ROOT}/components/libraries/log/src/nrf_log_default_backends.c
    ${NRF_SDK_ROOT}/components/libraries/log/src/nrf_log_backend_uart.c
    ${NRF_SDK_ROOT}/integration/nrfx/legacy/nrf_drv_uart.c
    ${NRF_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uarte.c
    ${NRF_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uart.c
    ${NRF_SDK_ROOT}/components/libraries/log/src/nrf_log_backend_serial.c
)

set(NRF5_SDK_INCLUDES
    ${NRF_SDK_ROOT}/components
    ${NRF_SDK_ROOT}/modules/nrfx/mdk
    ${NRF_SDK_ROOT}/components/libraries/strerror
    ${NRF_SDK_ROOT}/components/toolchain/cmsis/include
    ${NRF_SDK_ROOT}/components/libraries/util
    ${NRF_SDK_ROOT}/components/libraries/balloc
    ${NRF_SDK_ROOT}/components/libraries/ringbuf
    ${NRF_SDK_ROOT}/modules/nrfx/hal
    ${NRF_SDK_ROOT}/components/libraries/bsp
    ${NRF_SDK_ROOT}/components/libraries/log
    ${NRF_SDK_ROOT}/modules/nrfx
    ${NRF_SDK_ROOT}/components/libraries/experimental_section_vars
    ${NRF_SDK_ROOT}/components/libraries/delay
    ${NRF_SDK_ROOT}/integration/nrfx
    ${NRF_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
    ${NRF_SDK_ROOT}/components/libraries/atomic
    ${NRF_SDK_ROOT}/components/boards
    ${NRF_SDK_ROOT}/components/libraries/memobj
    ${NRF_SDK_ROOT}/external/fprintf
    ${NRF_SDK_ROOT}/components/libraries/log/src
    ${NRF_SDK_ROOT}/integration/nrfx/legacy
    ${NRF_SDK_ROOT}/modules/nrfx/drivers/include
)

set(NRF5_SDK_DEFINES
    BOARD_CUSTOM
    BSP_DEFINES_ONLY
    CONFIG_GPIO_AS_PINRESET
    FLOAT_ABI_HARD
    NRF52840_XXAA
    __HEAP_SIZE=8192
    __STACK_SIZE=8192
)

function(add_submodules TARGET)

    add_library(u8g2 STATIC ${U8G2_SOURCES})
    target_include_directories(u8g2 PRIVATE ${U8G2_INCLUDES})

    add_library(nrf5_sdk STATIC ${NRF5_SDK_SOURCES})
    target_include_directories(nrf5_sdk PRIVATE ${NRF5_SDK_INCLUDES})
    target_compile_definitions(nrf5_sdk PUBLIC ${NRF5_SDK_DEFINES})

    target_link_libraries(${TARGET} PRIVATE u8g2 nrf5_sdk)

    # Add include directories as SYSTEM for the main target to avoid treating library warnings as errors
    target_include_directories(${TARGET} SYSTEM PUBLIC ${U8G2_INCLUDES} ${NRF5_SDK_INCLUDES})
endfunction()
