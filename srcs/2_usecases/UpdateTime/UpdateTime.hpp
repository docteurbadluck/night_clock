#include "1_domain/Context/Context.hpp"
#include "3_interface/Clock.hpp"

namespace usecases {

class UpdateTime
{
private:
	interface::Clock &_clock;

public:
	UpdateTime(interface::Clock &clock);
	~UpdateTime() = default;
	void	updateCurrentTime(domain::Context &ctx);
};

}