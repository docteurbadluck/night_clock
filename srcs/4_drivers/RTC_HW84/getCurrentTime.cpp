#include "RTC_HW84.hpp"
#include <iomanip>
#include <sstream>

namespace drivers
{

std::string RTC_HW84::getCurrentTime()
{
	const auto raw = requestGetTime();
	if (!raw)
		return "";
	return parseTime(*raw);
}

std::optional<std::array<uint8_t, 3>> RTC_HW84::requestGetTime()
{
	constexpr uint8_t reg = 0x00;
	std::array<uint8_t, 3> raw;

	if (i2c_write_timeout_us(_i2c, ADDR, &reg, 1, true, I2C_TIMEOUT_US) != 1)
		return std::nullopt;
	if (i2c_read_timeout_us(_i2c, ADDR, raw.data(), 3, false, I2C_TIMEOUT_US) != 3)
		return std::nullopt;
	return raw;
}

std::string RTC_HW84::parseTime(const std::array<uint8_t, 3>& raw)
{
	const auto s = bcd_to_dec(raw[0] & 0x7F);
	const auto m = bcd_to_dec(raw[1] & 0x7F);
	const auto h = bcd_to_dec(raw[2] & 0x3F);

	std::ostringstream oss;
	oss << std::setfill('0')
		<< std::setw(2) << +h << ':'
		<< std::setw(2) << +m << ':'
		<< std::setw(2) << +s;
	return oss.str();
}

} // namespace drivers
