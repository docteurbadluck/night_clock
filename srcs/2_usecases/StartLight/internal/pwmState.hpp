#pragma once
#include <stdint.h>

namespace usecases {

enum LampState
{
	OFF,
	RISING,
	FIX,
	FALLING
};

struct pwmState
{
	float		current_intensity = 0.0f;
	LampState	state				 = OFF;
	uint16_t	fix_ticks_remaining	 = 0;
};

}