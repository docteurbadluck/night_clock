#include "2_usecases/StartLight/StartLight.hpp"

namespace usecases {

void StartLight::start()
{
	state.state = RISING;
	state.current_intensity = 0.0f;
	pwm.apply_duty(0.0f);
}

void StartLight::rising()
{
	float duty_step = max_intensity / rise_steps;

	state.current_intensity += duty_step;
	if (state.current_intensity >= max_intensity)
	{
		state.current_intensity = max_intensity;
		state.state = FIX;
		state.fix_ticks_remaining = fix_ticks;
	}
	pwm.apply_duty(state.current_intensity);
}

void StartLight::fix()
{
	state.fix_ticks_remaining--;
	if (state.fix_ticks_remaining == 0)
		state.state = FALLING;
}

void StartLight::falling(domain::Context &ctx)
{
	float duty_step = max_intensity / fall_steps;

	state.current_intensity -= duty_step;
	if (state.current_intensity <= duty_step * 0.5f)
	{
		state.current_intensity = 0.0f;
		state.state = OFF;
		pwm.apply_duty(0.0f);
		ctx.setFinishAction(true);
	}
	else
		pwm.apply_duty(state.current_intensity);
}

}
