#include "../HCSR04.hpp"
#include "hardware/gpio.h"
#include "pico/time.h"

namespace drivers
{

void HCSR04::trig()
{
	gpio_put(_pin_trig, false);
	sleep_us(2);
	gpio_put(_pin_trig, true);
	sleep_us(10);
	gpio_put(_pin_trig, false);
}

uint64_t HCSR04::getEchoTime()
{
	uint64_t timeout = time_us_64() + 30000;
	while (gpio_get(_pin_echo) == false)
	{
		if (time_us_64() > timeout)
			return 0;
	}
	uint64_t start_time = time_us_64();

	while(gpio_get(_pin_echo) == true)
	{
		if (time_us_64() > timeout)
			return 0;
	}
	return (time_us_64() - start_time);
}

uint32_t HCSR04::timeToDistanceCm(uint64_t pulseDurationUs) const
{
	return static_cast<uint32_t>(pulseDurationUs / 58);
}

}