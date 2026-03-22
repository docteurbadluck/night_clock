#include "RTC_HW84.hpp"

namespace drivers {

RTC_HW84::RTC_HW84(i2c_inst_t *i2c)
	: _i2c(i2c)
{
}

uint8_t RTC_HW84::bcd_to_dec(uint8_t bcd)
{
	return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t RTC_HW84::dec_to_bcd(uint8_t dec)
{
	return ((dec / 10) << 4) | (dec % 10);
}

} // namespace drivers
