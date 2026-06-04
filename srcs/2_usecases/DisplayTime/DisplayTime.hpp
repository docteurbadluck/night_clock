#include "1_domain/Context/Context.hpp"
#include "3_interface/Screen.hpp"

namespace usecases
{

class DisplayTime
{
	private:
		interface::Screen &_screen;
		std::string        _last_time;
public:
	DisplayTime(interface::Screen &screen);
	~DisplayTime() = default;
	void displayCurrentTime(const domain::Context &ctx);
};

DisplayTime::DisplayTime(interface::Screen &screen) : _screen(screen), _last_time("")
{
}

void DisplayTime::displayCurrentTime(const domain::Context &ctx)
{
	const std::string current = ctx.getCurrentTime();
	if (current.size() < 5 || current.substr(0, 5) == _last_time)
		return;
	_last_time = current.substr(0, 5);
	_screen.display(current);
}

}