#include "pico_pwm.hpp"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

namespace drivers
{

pico_pwm::pico_pwm(uint8_t pin, uint8_t adc_pin, float shunt_ohm)
	: _pin(pin), _adc_pin(adc_pin), _shunt_ohm(shunt_ohm)
{
	gpio_set_function(pin, GPIO_FUNC_PWM);
	_slice   = pwm_gpio_to_slice_num(pin);
	_channel = pwm_gpio_to_channel(pin);
	pwm_set_wrap(_slice, 255);
	pwm_set_enabled(_slice, true);
	pwm_set_chan_level(_slice, _channel, 0);

	if (_adc_pin != 0xFF)
	{
		adc_init();
		adc_gpio_init(_adc_pin);
	}
}

float pico_pwm::_read_current() const
{
	adc_select_input(_adc_pin - 26);
	float voltage = adc_read() * 3.3f / 4095.0f;
	return voltage / _shunt_ohm;
}

void pico_pwm::apply_duty(float intensity)
{
	pwm_set_chan_level(_slice, _channel, (uint8_t)(intensity * 255));
}

}