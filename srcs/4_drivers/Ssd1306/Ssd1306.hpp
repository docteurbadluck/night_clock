#pragma once
#include "3_interface/Screen.hpp"
#include "hardware/i2c.h"
extern "C" {
#include "ssd1306.h"
#include <stdio.h>
}

namespace drivers
{

class Ssd1306 : public interface::Screen
{
public:
	Ssd1306(i2c_inst_t *i2c);
	~Ssd1306() = default;

	void display(const std::string &time) override;

private:
	ssd1306_t _disp = {};


	static constexpr uint8_t SSD1306_ADDR   = 0x3C;
	static constexpr uint    SSD1306_WIDTH  = 128;
	static constexpr uint    SSD1306_HEIGHT = 32;
	void _drawOutline(const char *s, uint32_t x, uint32_t y, uint32_t scale);
	void _drawHollow(const char *s, uint32_t x, uint32_t y, uint32_t scale);
};

} // namespace drivers
