cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico2_w)
set(CMAKE_BUILD_TYPE Debug)
include(pico_sdk_import.cmake)
project(IGPIO C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.cpp)

add_executable(night_clock
	${APP_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/libs/pico-ssd1306/ssd1306.c
)

if(NOT DEFINED START_TIME)
    string(TIMESTAMP START_TIME "%H:%M:%S")
endif()
target_compile_definitions(night_clock PRIVATE START_TIME="${START_TIME}")

target_link_libraries(night_clock pico_stdlib hardware_pwm hardware_spi hardware_i2c hardware_adc)
target_include_directories(night_clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/pico-ssd1306)
pico_enable_stdio_usb(night_clock 0)
pico_enable_stdio_uart(night_clock 1)
pico_add_extra_outputs(night_clock)
target_compile_options(night_clock PRIVATE $<$<CONFIG:Debug>:-Og>)
target_include_directories(night_clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/srcs)
