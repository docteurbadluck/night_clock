#include "2_usecases/UpdateTime/UpdateTime.hpp"

namespace usecases {

void	UpdateTime::updateCurrentTime(domain::Context &ctx)
{
	ctx.setCurrentTime(_clock.getCurrentTime());
}
}