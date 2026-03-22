#include "1_domain/Context/Context.hpp"
#include "3_interface/Screen.hpp"

namespace usecases
{

class DisplayTime
{
	private:
		interface::Screen &_screen;
public:
	DisplayTime(interface::Screen &screen);
	~DisplayTime() = default;
	void displayCurrentTime(const domain::Context &ctx);
};

DisplayTime::DisplayTime(interface::Screen &screen) : _screen(screen)
{
}

void DisplayTime::displayCurrentTime(const domain::Context &ctx)
{
	_screen.display(ctx.getCurrentTime());
}

}