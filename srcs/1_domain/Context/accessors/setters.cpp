#include "1_domain/Context/Context.hpp"

namespace domain
{

void Context::setInput(bool test_button_state, bool movement_sensor_state)
{
	test_button_pressed = test_button_state;
	movement_detected = movement_sensor_state;
}


void Context::setMovementDetected(bool movement_sensor_state)
{
	movement_detected = movement_sensor_state;
}


void Context::setFinishAction(bool action_state)
{
	action_finished = action_state;
}

void Context::setCurrentTime(const std::string &time_str)
{
	this->current_time = Time(time_str);
}
}