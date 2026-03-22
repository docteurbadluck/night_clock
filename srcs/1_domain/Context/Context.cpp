#include "Context.hpp"

namespace domain
{

Context::Context(std::string current_time,
			std::string night_start,
			std::string night_end) : 
			current_time(current_time),
			night_start(night_start),
			night_end(night_end)
{
		this->state = SLEEPY;
		this->movement_detected = false;
		this->test_button_pressed = false;
		this->action_finished = false;
		this->computeState();
}

Context::Context() :
			current_time("10:00:00"),
			night_start("21:00:00"),
			night_end("07:00:00")
{
		this->state = SLEEPY;
		this->movement_detected = false;
		this->test_button_pressed = false;
		this->action_finished = false;
		this->computeState();
}

}