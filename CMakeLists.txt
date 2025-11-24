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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(blinky_pca10056 LANGUAGES C CXX ASM)

set(PROJ_DIR ${CMAKE_SOURCE_DIR}/src)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/nrf52840_s140_v7.ld)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(SRC_FILES
    src/main.c
)

include_directories(
    src  # TODO: hide from library cmake files
    src/config
)

set(MCU_FLAGS
    -O3
    -g3
    -mcpu=cortex-m4
    -mthumb
    -mabi=aapcs
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -ffunction-sections
    -fdata-sections
    -fno-strict-aliasing
    -fno-builtin
    -fshort-enums
)

string(JOIN " " MCU_FLAGS_STR ${MCU_FLAGS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS_STR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS_STR}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${MCU_FLAGS_STR}")

add_subdirectory(lib)
add_executable(blinky ${SRC_FILES})  # TODO: rename target

target_compile_options(blinky PRIVATE
    -Wall
    -Werror
)

target_link_options(blinky PRIVATE
    -Llib/nrf5_sdk/modules/nrfx/mdk
    -T${LINKER_SCRIPT}
    -Wl,--gc-sections
    --specs=nano.specs
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/blinky.map
)

target_link_libraries(blinky PRIVATE
    c
    nosys
    m
    u8g2
    nrf5_sdk
)

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

add_custom_command(
    TARGET blinky POST_BUILD
    COMMAND cksum ARGS blinky.bin
    COMMENT "Checksum of blinky.bin"
)
