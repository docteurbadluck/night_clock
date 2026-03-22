#include "0_orchestration/loop.hpp"
#include "1_domain/Context/Context.hpp"

int main()
{
	stdio_init_all();
	orchestration::init_i2c();
	orchestration::init_test_button();

	orchestration::Drivers	drivers(i2c0);
	orchestration::Usecases	uc(drivers);
	domain::Context			ctx("00:00:00", "21:00:00", "07:00:00");

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
