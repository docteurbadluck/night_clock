#pragma once
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

namespace orchestration {

static constexpr uint TEST_PIN = 13;

inline void init_i2c()
{
	i2c_init(i2c0, 400000);
	gpio_set_function(4, GPIO_FUNC_I2C);
	gpio_set_function(5, GPIO_FUNC_I2C);
	gpio_pull_up(4);
	gpio_pull_up(5);
}

inline void init_test_button()
{
	gpio_init(TEST_PIN);
	gpio_set_dir(TEST_PIN, GPIO_IN);
	gpio_pull_up(TEST_PIN);
}

}
