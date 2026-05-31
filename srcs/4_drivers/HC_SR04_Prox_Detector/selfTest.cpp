#include "HCSR04.hpp"

namespace drivers {

bool HCSR04::selfTest()
{
	trig();
	return getEchoTime() != 0;
}

} // namespace drivers
