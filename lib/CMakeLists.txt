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

target_compile_options(u8g2 PRIVATE
    -O3
    -g3
    -mcpu=cortex-m4
    -mthumb
    -mabi=aapcs
    -Wall
    -Werror
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -ffunction-sections
    -fdata-sections
    -fno-strict-aliasing
    -fno-builtin
    -fshort-enums
)

target_compile_definitions(u8g2 PRIVATE
    BOARD_CUSTOM
    BSP_DEFINES_ONLY
    CONFIG_GPIO_AS_PINRESET
    FLOAT_ABI_HARD
    NRF52840_XXAA
    __HEAP_SIZE=8192
    __STACK_SIZE=8192
)
