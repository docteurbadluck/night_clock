#include "2_usecases/StartLight/StartLight.hpp"

namespace usecases {

void StartLight::tick(domain::Context &ctx)
{
	if (state.state == OFF && ctx.getState() == domain::ACTIVE)
	{
		start();
		return ;
	}

	if (state.state == RISING)
		rising();
	else if (state.state == FIX)
		fix();
	else if (state.state == FALLING)
		falling(ctx);
}

}
