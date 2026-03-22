#pragma once
#include "0_orchestration/Drivers.hpp"
#include "2_usecases/UpdateTime/UpdateTime.hpp"
#include "2_usecases/DisplayTime/DisplayTime.hpp"
#include "2_usecases/DetectProx/DetectProx.hpp"
#include "2_usecases/StartLight/StartLight.hpp"

namespace orchestration {

struct Usecases
{
	static constexpr uint16_t TICK_MS = 50;

	usecases::UpdateTime  update_time;
	usecases::DisplayTime display_time;
	usecases::DetectProx  detect_prox;
	usecases::StartLight  start_light;

	Usecases(Drivers &drivers)
		: update_time(drivers.rtc),
		  display_time(drivers.screen),
		  detect_prox(drivers.prox),
		  start_light(drivers.led, 3, 10, 3, 0.8f, TICK_MS)
	{}
};

}
