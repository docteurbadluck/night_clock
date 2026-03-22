#include "HCSR04.hpp"

namespace drivers
{

bool HCSR04::triggered()
{
	trig();
	uint64_t echo = getEchoTime();
	uint32_t res = timeToDistanceCm(echo);
	if (res == 0)
		return false;

	return (res < _distance_cm);
}
}