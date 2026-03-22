#include "1_domain/Context/Context.hpp"

namespace domain
{
State Context::getState() const
{
	return this->state;
}

bool Context::getMovementDetected() const
{
	return this->movement_detected;
}

bool Context::getActionFinished() const
{
	return this->action_finished;
}

std::string Context::getCurrentTime() const
{
	return this->current_time.toString();
}


}