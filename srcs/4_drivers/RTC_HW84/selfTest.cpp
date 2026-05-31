#include "RTC_HW84.hpp"

namespace drivers {

bool RTC_HW84::selfTest()
{
	return requestGetTime().has_value();
}

} // namespace drivers
