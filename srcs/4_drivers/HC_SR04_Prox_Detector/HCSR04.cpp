#include "HCSR04.hpp"
#include "hardware/gpio.h"

namespace drivers
{


HCSR04::HCSR04(uint8_t pin_trig, uint8_t pin_echo, uint8_t distance_cm) : 
			   _pin_trig(pin_trig),
			   _pin_echo(pin_echo), 
			   _distance_cm(distance_cm)
{
	gpio_init(pin_trig);
	gpio_set_dir(pin_trig, true);
	gpio_put(pin_trig, false);

	gpio_init(pin_echo);
	gpio_set_dir(pin_echo, false);
	gpio_pull_down(pin_echo);
}


}