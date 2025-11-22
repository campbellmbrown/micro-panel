cmake_minimum_required(VERSION 3.25)

set(C_STANDARD 99)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_EXECUTABLE_SUFFIX_C .out)
set(CMAKE_C_SIZE_TOOL arm-none-eabi-size)

# Required to prevent "The C Compiler is not able to compile a simple test program"
# error due to cross-compiling.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_BINARY_DIR build)

project(blinky_pca10056 LANGUAGES C CXX ASM)

# Cross-compile settings
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_EXECUTABLE_SUFFIX .out)
set(CMAKE_C_SIZE_TOOL arm-none-eabi-size)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

set(SDK_ROOT ${CMAKE_SOURCE_DIR}/lib/nrf5_sdk)
set(PROJ_DIR ${CMAKE_SOURCE_DIR}/src)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/nrf52840_s140_v7.ld)

# Source files
set(SRC_FILES
    ${SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
    ${SDK_ROOT}/components/libraries/log/src/nrf_log_str_formatter.c
    ${SDK_ROOT}/components/libraries/util/app_error.c
    ${SDK_ROOT}/components/libraries/util/app_error_handler_gcc.c
    ${SDK_ROOT}/components/libraries/util/app_error_weak.c
    ${SDK_ROOT}/components/libraries/util/app_util_platform.c
    ${SDK_ROOT}/components/libraries/util/nrf_assert.c
    ${SDK_ROOT}/components/libraries/atomic/nrf_atomic.c
    ${SDK_ROOT}/components/libraries/balloc/nrf_balloc.c
    ${SDK_ROOT}/external/fprintf/nrf_fprintf.c
    ${SDK_ROOT}/external/fprintf/nrf_fprintf_format.c
    ${SDK_ROOT}/components/libraries/memobj/nrf_memobj.c
    ${SDK_ROOT}/components/libraries/ringbuf/nrf_ringbuf.c
    ${SDK_ROOT}/components/libraries/strerror/nrf_strerror.c
    ${SDK_ROOT}/modules/nrfx/soc/nrfx_atomic.c
    ${PROJ_DIR}/main.c
    ${SDK_ROOT}/modules/nrfx/mdk/system_nrf52840.c
)

# Include directories
include_directories(
    ${SDK_ROOT}/components
    ${SDK_ROOT}/modules/nrfx/mdk
    ${PROJ_DIR}
    ${PROJ_DIR}/config
    ${SDK_ROOT}/components/libraries/strerror
    ${SDK_ROOT}/components/toolchain/cmsis/include
    ${SDK_ROOT}/components/libraries/util
    ${SDK_ROOT}/components/libraries/balloc
    ${SDK_ROOT}/components/libraries/ringbuf
    ${SDK_ROOT}/modules/nrfx/hal
    ${SDK_ROOT}/components/libraries/bsp
    ${SDK_ROOT}/components/libraries/log
    ${SDK_ROOT}/modules/nrfx
    ${SDK_ROOT}/components/libraries/experimental_section_vars
    ${SDK_ROOT}/components/libraries/delay
    ${SDK_ROOT}/integration/nrfx
    ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
    ${SDK_ROOT}/components/libraries/atomic
    ${SDK_ROOT}/components/boards
    ${SDK_ROOT}/components/libraries/memobj
    ${SDK_ROOT}/external/fprintf
    ${SDK_ROOT}/components/libraries/log/src
)

# Add executable
add_executable(blinky ${SRC_FILES})

# Compiler definitions
target_compile_definitions(blinky PRIVATE
    BOARD_CUSTOM
    BSP_DEFINES_ONLY
    CONFIG_GPIO_AS_PINRESET
    FLOAT_ABI_HARD
    NRF52840_XXAA
    __HEAP_SIZE=8192
    __STACK_SIZE=8192
)

# Compiler options
target_compile_options(blinky PRIVATE
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

# Linker options
target_link_options(blinky PRIVATE
    -O3
    -g3
    -mthumb
    -mabi=aapcs
    -L${SDK_ROOT}/modules/nrfx/mdk
    -T${LINKER_SCRIPT}
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -Wl,--gc-sections
    --specs=nano.specs
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/blinky.map
)

# Link standard libraries
target_link_libraries(blinky PRIVATE
    c
    nosys
    m
)

# Generate binary and hex
add_custom_command(
    TARGET blinky POST_BUILD
    COMMAND ${CMAKE_C_SIZE_TOOL} ARGS blinky.out
    COMMENT "Size of blinky.out"
)

add_custom_command(
    TARGET blinky POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary blinky.out blinky.bin
    COMMENT "Generating blinky.bin"
)

add_custom_command(
    TARGET blinky POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex blinky.out blinky.hex
    COMMENT "Generating blinky.hex"
)
