#include "Ssd1306.hpp"

namespace drivers {

bool Ssd1306::selfTest()
{
	if (_disp.address == 0)
		return false;
	display("88:88:88");
	sleep_ms(500);
	ssd1306_clear(&_disp);
	ssd1306_show(&_disp);
	return true;
}

} // namespace drivers
