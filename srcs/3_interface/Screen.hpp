#pragma once
#include <string>
namespace interface
{

class Screen
{
public:
	virtual ~Screen()= default;
	virtual void	display(const std::string &time) = 0;
	virtual bool	selfTest() = 0;
};

}