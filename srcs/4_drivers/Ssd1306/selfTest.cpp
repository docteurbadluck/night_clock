#include "Ssd1306.hpp"

namespace drivers {

bool Ssd1306::selfTest()
{
	return _disp.address != 0;
}

} // namespace drivers
