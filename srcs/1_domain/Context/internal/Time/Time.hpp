#include <string>
#include <cstdint>

class Time 
{
	public :
		Time(std::string time);
		~Time() = default;
		Time& operator=(const Time&) = default;
		
		
		uint8_t	hour;
		uint8_t	minute;
		uint8_t	second;

		bool		is_between(const Time &start, const Time &end) const ;
		bool		operator>(const Time &a) const;
		bool		operator<(const Time &a) const;
		bool		operator==(const Time &a) const;
		bool		operator!=(const Time &a) const;
		bool		operator>=(const Time &a) const;
		bool		operator<=(const Time &a) const;
		std::string	toString() const;
};


