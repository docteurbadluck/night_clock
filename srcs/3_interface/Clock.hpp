#pragma once
#include <string>

namespace interface {
	
class Clock
{
	public:
		virtual ~Clock() = default;
		virtual std::string getCurrentTime() = 0;
};

}