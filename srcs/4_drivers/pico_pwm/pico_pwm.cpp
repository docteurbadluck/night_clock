#include "pico_pwm.hpp"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

namespace drivers
{

pico_pwm::pico_pwm(uint8_t pin) : _pin(pin)
{
	gpio_set_function(pin, GPIO_FUNC_PWM);
	_slice   = pwm_gpio_to_slice_num(pin);
	_channel = pwm_gpio_to_channel(pin);
	pwm_set_wrap(_slice, 255);
	pwm_set_enabled(_slice, true);
	pwm_set_chan_level(_slice, _channel, 0);
}

void pico_pwm::apply_duty(float intensity)
{
	pwm_set_chan_level(_slice, _channel, (uint8_t)(intensity * 255));
}

}