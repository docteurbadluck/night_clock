
#include "0_orchestration/loop.hpp"
#include "1_domain/Context/Context.hpp"


int main()
{
	stdio_init_all();
	sleep_ms(2000);
	printf("Welcome on pico :\n");

	orchestration::init_i2c();
	printf("init i2c succesfull\n");

	orchestration::init_test_button();
	orchestration::init_error_led();

	orchestration::Drivers	drivers(i2c0);
	if (!orchestration::run_self_tests(drivers))
	{
		gpio_put(orchestration::ERROR_LED_PIN, 1);
		return 1;
	}
	orchestration::Usecases	uc(drivers);
	domain::Context			ctx("00:00:00", "21:00:00", "07:00:00");
	printf("init successfull\n");
	return 0;

	absolute_time_t next_tick = get_absolute_time();
	while (true)
	{
		next_tick = delayed_by_ms(next_tick, uc.TICK_MS);
		orchestration::update_context(uc, ctx);
		orchestration::compute_context(uc, ctx);
		sleep_until(next_tick);
	}
	return 0;
}

/*
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "4_drivers/Ssd1306/Ssd1306.hpp"

int main()
{
	stdio_init_all();
	while (!stdio_usb_connected())
		sleep_ms(100);
	printf("=== screen test ===\n");

	printf("init i2c...\n");
	i2c_init(i2c0, 100000);
	gpio_set_function(4, GPIO_FUNC_I2C);
	gpio_set_function(17, GPIO_FUNC_I2C);
	gpio_pull_up(4);
	gpio_pull_up(17);
	printf("i2c ok\n");

	printf("scanning i2c bus...\n");
	for (uint8_t addr = 0x08; addr < 0x78; addr++)
	{
		uint8_t buf;
		int ret = i2c_read_blocking(i2c0, addr, &buf, 1, false);
		if (ret >= 0)
			printf("device found at 0x%02X\n", addr);
	}
	printf("scan done\n");
	return 0;
}
*/

/*

#include "stdio.h"
#include "pico/stdlib.h"

int main()
{
	stdio_init_all();
	int pin = 17;
	gpio_init(pin);
	gpio_set_dir(pin, true);

	gpio_put(pin, 1);
	while (true)
	{
		gpio_put(pin, 0);
		printf("hello\n");
		sleep_ms(2000);
		gpio_put(pin, 1);
		sleep_ms(2000);
	}


	return 0;
}
*/