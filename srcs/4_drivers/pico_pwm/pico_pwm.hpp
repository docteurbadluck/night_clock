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

	public:
		pico_pwm(uint8_t pin);
		~pico_pwm() = default;
		void	apply_duty(float intensity) override;
};

}