#include "../Context.hpp"

namespace domain
{


bool Context::isNight()
{
	return(this->current_time.is_between(this->night_start, this->night_end));
}

}