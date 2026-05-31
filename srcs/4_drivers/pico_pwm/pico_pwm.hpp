#include "3_interface/pwm.hpp"
#include "pico/types.h"
#include <cstdint>

namespace drivers
{

class pico_pwm : public interface::PWM
{
	private:
		uint8_t	_pin;
		uint	_slice;
		uint	_channel;
		uint8_t	_adc_pin;    // 0xFF = no shunt
		float	_shunt_ohm;

		float	_read_current() const;

	public:
		pico_pwm(uint8_t pin, uint8_t adc_pin = 0xFF, float shunt_ohm = 0.333f);
		~pico_pwm() = default;
		void	apply_duty(float intensity) override;
		bool	selfTest() override;
};

}