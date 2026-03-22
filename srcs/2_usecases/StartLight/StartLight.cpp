#include "2_usecases/StartLight/StartLight.hpp"

namespace usecases {

StartLight::StartLight(interface::PWM &pwm,
                       uint16_t rise_seconde_duration, uint16_t fix_seconde_duration, uint16_t fall_seconde_duration,
                       float max_intensity, uint16_t period_ms_per_tick)
	: pwm(pwm),
	  rise_steps((rise_seconde_duration * 1000) / period_ms_per_tick),
	  fix_ticks((fix_seconde_duration * 1000) / period_ms_per_tick),
	  fall_steps((fall_seconde_duration * 1000) / period_ms_per_tick),
	  max_intensity(max_intensity)
{
}

}
