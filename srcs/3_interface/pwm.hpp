#pragma once
#include "stdint.h"
namespace interface {
	
class PWM
{
	public:
		virtual ~PWM() = default;
		virtual void apply_duty(float intensity) = 0;
		virtual bool selfTest() = 0;
};

}