#include "Ssd1306.hpp"

namespace drivers
{

Ssd1306::Ssd1306(i2c_inst_t *i2c)
{
	sleep_ms(100);
	uint8_t dummy = 0;
	if (i2c_write_timeout_us(i2c, SSD1306_ADDR, &dummy, 1, false, 1000) == 1)
		ssd1306_init(&_disp, SSD1306_WIDTH, SSD1306_HEIGHT, SSD1306_ADDR, i2c);
}

} // namespace drivers
