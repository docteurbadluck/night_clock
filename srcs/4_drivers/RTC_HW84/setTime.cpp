#include "RTC_HW84.hpp"
#include <iomanip>
#include <sstream>

namespace drivers
{

void RTC_HW84::setTime(const std::string &time)
{
	auto buffer = parsePutRequest(time);
	if (!buffer)
		return;
	i2c_write_timeout_us(_i2c, ADDR, buffer->data(), 4, false, I2C_TIMEOUT_US);
}

std::optional<std::array<uint8_t, 4>> RTC_HW84::parsePutRequest(const std::string &time)
{
	int h, m, s;
	std::array<uint8_t, 4> buffer;

	if (sscanf(time.c_str(), "%d:%d:%d", &h, &m, &s) != 3)
		return std::nullopt;
	if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
		return std::nullopt;

	buffer[0] = 0x00;
	buffer[1] = dec_to_bcd(s);
	buffer[2] = dec_to_bcd(m);
	buffer[3] = dec_to_bcd(h);

	return buffer;
}

} // namespace drivers
