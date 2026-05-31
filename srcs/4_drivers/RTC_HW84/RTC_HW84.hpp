#pragma once
#include "3_interface/Clock.hpp"
#include "hardware/i2c.h"
#include <array>
#include <optional>
#include <string>

namespace drivers {

class RTC_HW84 : public interface::Clock
{
	public:
		RTC_HW84(i2c_inst_t *i2c);
		~RTC_HW84() = default;
	
		std::string	getCurrentTime() override;
		void		setTime(const std::string &time);
		bool		selfTest() override;
	
	private:
		i2c_inst_t *_i2c;
		static constexpr uint8_t  ADDR = 0x68;
		static constexpr uint      I2C_TIMEOUT_US = 1000;
	
		std::optional<std::array<uint8_t, 3>> requestGetTime();
		std::string parseTime(const std::array<uint8_t, 3>& raw);
		std::optional<std::array<uint8_t, 4>> parsePutRequest(const std::string &time);
		uint8_t bcd_to_dec(uint8_t bcd);
		uint8_t dec_to_bcd(uint8_t dec);
};

} // namespace drivers
