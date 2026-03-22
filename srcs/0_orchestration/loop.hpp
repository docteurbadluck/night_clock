#pragma once
#include "hardware/gpio.h"
#include "0_orchestration/init.hpp"
#include "0_orchestration/Usecases.hpp"
#include "1_domain/Context/Context.hpp"

namespace orchestration {

inline void update_context(Usecases &uc, domain::Context &ctx)
{
	uc.update_time.updateCurrentTime(ctx);
	uc.detect_prox.updateDetectedState(ctx);
	bool test_pressed = !gpio_get(TEST_PIN);
	ctx.setInput(test_pressed, ctx.getMovementDetected());
}

inline void compute_context(Usecases &uc, domain::Context &ctx)
{
	ctx.computeState();
	uc.start_light.tick(ctx);
	uc.display_time.displayCurrentTime(ctx);
}

}
