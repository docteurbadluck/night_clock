#pragma once
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "0_orchestration/Drivers.hpp"
#include <cstdio>

namespace orchestration {

static constexpr uint TEST_PIN     = 13;
static constexpr uint ERROR_LED_PIN = 17;

inline void init_error_led()
{
	gpio_init(ERROR_LED_PIN);
	gpio_set_dir(ERROR_LED_PIN, GPIO_OUT);
	gpio_put(ERROR_LED_PIN, 0);
}

inline void init_i2c()
{
	i2c_init(i2c0, 400000);
	gpio_set_function(4, GPIO_FUNC_I2C);
	gpio_set_function(9, GPIO_FUNC_I2C);
	gpio_pull_up(4);
	gpio_pull_up(9);
}

inline void init_test_button()
{
	gpio_init(TEST_PIN);
	gpio_set_dir(TEST_PIN, GPIO_IN);
	gpio_pull_up(TEST_PIN);
}

inline bool run_self_tests(Drivers &drivers)
{
	bool led_ok    = drivers.led.selfTest();
	bool rtc_ok    = drivers.rtc.selfTest();
	bool screen_ok = drivers.screen.selfTest();
	bool prox_ok   = drivers.prox.selfTest();

	if (!led_ok)    printf("ERROR: LED not responding\n");
	if (!rtc_ok)    printf("ERROR: RTC not responding\n");
	if (!screen_ok) printf("ERROR: Screen not responding\n");
	if (!prox_ok)   printf("ERROR: Proximity sensor not responding\n");

	return led_ok && rtc_ok && screen_ok && prox_ok;
}

}
