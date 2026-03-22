#include "../Ssd1306.hpp"
#include "font_modern.h"

namespace drivers
{
// Même logique que ssd1306_draw_string_with_font mais efface les pixels
static void clear_string(ssd1306_t *disp, uint32_t x, uint32_t y,
                          uint32_t scale, const uint8_t *font, const char *s)
{
	const uint32_t parts_per_line = (font[0] >> 3) + ((font[0] & 7) > 0);

	for (uint32_t x_n = x; *s; x_n += (font[1] + font[2]) * scale, ++s) {
		const char c = *s;
		if (c < font[3] || c > font[4])
			continue;
		for (uint8_t w = 0; w < font[1]; ++w) {
			uint32_t pp = (c - font[3]) * font[1] * parts_per_line + w * parts_per_line + 5;
			for (uint32_t lp = 0; lp < parts_per_line; ++lp) {
				uint8_t line = font[pp++];
				for (int8_t j = 0; j < 8; ++j, line >>= 1)
					if (line & 1)
						ssd1306_clear_square(disp,
							x_n + w * scale,
							y + (lp * 8 + j) * scale,
							scale, scale);
			}
		}
	}
}

void Ssd1306::_drawOutline(const char *s, uint32_t x, uint32_t y, uint32_t scale)
{
	ssd1306_draw_string_with_font(&_disp, x - 1, y,     scale, font_modern, s);
	ssd1306_draw_string_with_font(&_disp, x + 1, y,     scale, font_modern, s);
	ssd1306_draw_string_with_font(&_disp, x,     y - 1, scale, font_modern, s);
	ssd1306_draw_string_with_font(&_disp, x,     y + 1, scale, font_modern, s);
}

void Ssd1306::_drawHollow(const char *s, uint32_t x, uint32_t y, uint32_t scale)
{
	clear_string(&_disp, x, y, scale, font_modern, s);
}

}