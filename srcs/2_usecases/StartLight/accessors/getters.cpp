#include "2_usecases/StartLight/StartLight.hpp"

namespace usecases
{

pwmState StartLight::getPwmState() const
{
	return this->state;
}

}
