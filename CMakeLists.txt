cmake_minimum_required(VERSION 3.13)
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

target_link_libraries(night_clock pico_stdlib hardware_pwm hardware_spi hardware_i2c)
target_include_directories(night_clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/pico-ssd1306)
pico_enable_stdio_usb(night_clock 0)
pico_enable_stdio_uart(night_clock 1)
pico_add_extra_outputs(night_clock)
target_include_directories(night_clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/srcs)

#add_subdirectory(test)