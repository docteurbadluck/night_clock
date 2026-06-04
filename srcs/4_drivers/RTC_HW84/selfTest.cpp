#include "RTC_HW84.hpp"
#include <cstdio>

namespace drivers {

bool RTC_HW84::selfTest()
{
	const std::string test_time = "06:00:00";
	setTime(test_time);
	sleep_ms(100);

	const std::string read_back = getCurrentTime();
	if (read_back.size() < 8)
	{
		printf("RTC selfTest FAILED: I2C read failed\n");
		return false;
	}
	if (read_back.substr(0, 5) != test_time.substr(0, 5))
	{
		printf("RTC selfTest FAILED: expected %s got %s\n", test_time.c_str(), read_back.c_str());
		return false;
	}
	return true;
}

} // namespace drivers
