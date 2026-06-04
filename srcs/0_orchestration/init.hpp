#pragma once
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "0_orchestration/Drivers.hpp"
#include <cstdio>

namespace orchestration {

static constexpr uint TEST_PIN      = 10;
static constexpr uint ERROR_LED_PIN = 15;
static constexpr uint I2C_SDA_PIN   = 12;
static constexpr uint I2C_SCL_PIN   = 13;

inline void init_error_led()
{
	gpio_init(ERROR_LED_PIN);
	gpio_set_dir(ERROR_LED_PIN, GPIO_OUT);
	gpio_put(ERROR_LED_PIN, 0);
}

inline void init_i2c()
{
	i2c_init(i2c0, 400000);
	gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(I2C_SDA_PIN);
	gpio_pull_up(I2C_SCL_PIN);
}

inline void init_test_button()
{
	gpio_init(TEST_PIN);
	gpio_set_dir(TEST_PIN, GPIO_IN);
	gpio_pull_up(TEST_PIN);
}

inline bool run_self_tests(Drivers &drivers)
{
	bool rtc_ok    = drivers.rtc.selfTest();
	bool screen_ok = drivers.screen.selfTest();
	bool prox_ok   = drivers.prox.selfTest();
	bool led_ok    = drivers.led.selfTest();


	if (!led_ok)    printf("ERROR: LED not responding\n");
	if (!rtc_ok)    printf("ERROR: RTC not responding\n");
	if (!screen_ok) printf("ERROR: Screen not responding\n");
	if (!prox_ok)   printf("ERROR: Proximity sensor not responding\n");

	return led_ok && rtc_ok && screen_ok && prox_ok;
}

}
