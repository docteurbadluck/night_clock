#include "1_domain/Context/Context.hpp"
#include "3_interface/pwm.hpp"
#include "internal/pwmState.hpp"

namespace usecases
{

class StartLight
{
private:
	pwmState       state;
	interface::PWM &pwm;
	uint16_t       rise_steps;
	uint16_t       fix_ticks;
	uint16_t       fall_steps;
	float          max_intensity;

	void start();
	void rising();
	void fix();
	void falling(domain::Context &ctx);

public:
	pwmState getPwmState() const;
	StartLight(interface::PWM &pwm,
			   uint16_t rise_seconde_duration, uint16_t fix_seconde_duration, uint16_t fall_seconde_duration,
			   float max_intensity, uint16_t period_ms_per_tick);
	~StartLight() = default;
	void tick(domain::Context &ctx);
};

}