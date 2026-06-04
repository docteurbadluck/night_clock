
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
	drivers.rtc.setTime("22:30:00");
	orchestration::Usecases	uc(drivers);
	domain::Context			ctx("00:00:00", "21:00:00", "07:00:00");
	printf("init successfull\n");

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