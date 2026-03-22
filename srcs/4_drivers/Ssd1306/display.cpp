#include "Ssd1306.hpp"

namespace drivers
{

void Ssd1306::display(const std::string &time)
{
	constexpr uint32_t x     = 20;
	constexpr uint32_t y     = 4;
	constexpr uint32_t scale = 3;
	const std::string hhmm = time.substr(0, 5);
	const char *s = hhmm.c_str();

	ssd1306_clear(&_disp);
	_drawOutline(s, x, y, scale);
	_drawHollow(s, x, y, scale);
	ssd1306_show(&_disp);
}

} // namespace drivers
