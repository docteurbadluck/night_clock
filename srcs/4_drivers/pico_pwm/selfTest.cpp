#include "pico_pwm.hpp"
#include "pico/stdlib.h"
#include <stdio.h>

namespace drivers {

static constexpr float MIN_CURRENT_ON_A  = 0.050f; // 50 mA minimum quand allumé
static constexpr float MAX_CURRENT_OFF_A = 0.020f; // 20 mA maximum quand éteint (marge bruit ADC)

bool pico_pwm::selfTest()
{
	apply_duty(1.0f);
	sleep_ms(50);

	if (_adc_pin != 0xFF)
	{
		float current_on = _read_current();
		if (current_on < MIN_CURRENT_ON_A)
		{
			printf("LED selfTest: current ON  = %.1f mA\n", current_on * 1000.0f);
			printf("LED selfTest FAILED: no current detected\n");
			apply_duty(0.0f);
			return false;
		}
	}

	apply_duty(0.0f);
	sleep_ms(50);

	if (_adc_pin != 0xFF)
	{
		float current_off = _read_current();
		if (current_off > MAX_CURRENT_OFF_A)
		{
			printf("LED selfTest: current OFF = %.1f mA\n", current_off * 1000.0f);
			printf("LED selfTest FAILED: current still flowing when off\n");
			return false;
		}
	}

	return true;
}

} // namespace drivers
