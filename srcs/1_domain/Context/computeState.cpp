#include "Context.hpp"
#include <cstdio>
namespace domain
{

void Context::computeState()
{
	switch (this->state)
	{
	case SLEEPY:
		this->compute_sleepy_state();
		break;
	case READY:
		this->compute_ready_state();
		break;
	case ACTIVE:
		this->compute_active_state();
		break;
	default:
		printf("error, state set to SLEEPY\n");
		this->state = SLEEPY;
		break;
	}
}

void Context::compute_sleepy_state()
{
	if (test_button_pressed)
		this->state = ACTIVE;
	else if (this->isNight())
		this->state = READY;
}

void Context::compute_ready_state()
{
	if (this->isNight() == false)
		this->state = SLEEPY;
	else if (this->movement_detected)
		this->state = ACTIVE;
}

void Context::compute_active_state()
{
	if (this->action_finished)
	{
		this->action_finished = false;
		if (this->isNight())
			this->state = READY;
		else
			this->state = SLEEPY;
	}
}


}