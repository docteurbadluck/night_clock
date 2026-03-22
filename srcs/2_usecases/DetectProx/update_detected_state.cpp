#include "2_usecases/DetectProx/DetectProx.hpp"

namespace usecases {

void	DetectProx::updateDetectedState(domain::Context &ctx)
{
	ctx.setMovementDetected(proxDetector.triggered());
}
}