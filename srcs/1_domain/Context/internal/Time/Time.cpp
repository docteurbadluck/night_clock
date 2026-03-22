#include "Time.hpp"

Time::Time(std::string time)
{
	this->hour = atoi(time.substr(0, 2).c_str());
	this->minute = atoi(time.substr(3, 2).c_str());
	this->second = atoi(time.substr(6, 2).c_str()); 
}

bool Time::operator>(const Time &a) const
{
	if (hour != a.hour)
		return hour > a.hour;
	if (minute != a.minute)
		return minute > a.minute;
	return second > a.second;
}

bool Time::operator<(const Time &a) const
{
	if (hour != a.hour)
		return hour < a.hour;
	if (minute != a.minute)
		return minute < a.minute;
	return second < a.second;
}

bool Time::operator==(const Time &a) const
{
	return hour == a.hour && minute == a.minute && second == a.second;
}

bool Time::operator!=(const Time &a) const
{
	return !(*this == a);
}

bool Time::operator>=(const Time &a) const
{
	return (*this > a) || (*this == a);
}

bool Time::operator<=(const Time &a) const
{
	return (*this < a) || (*this == a);
}

bool Time::is_between(const Time &start, const Time &end) const
{
	if (start <= end)
		return (*this >= start) && (*this <= end);
	
	return (*this >= start) || (*this <= end);
}

std::string Time::toString() const
{
	auto pad = [](int v) {
		return (v < 10 ? "0" : "") + std::to_string(v);
	};
	return pad(this->hour) + ":" + pad(this->minute) + ":" + pad(this->second);
}