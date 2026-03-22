#pragma once
#include "hardware/i2c.h"
#include "4_drivers/Ssd1306/Ssd1306.hpp"
#include "4_drivers/RTC_HW84/RTC_HW84.hpp"
#include "4_drivers/HC_SR04_Prox_Detector/HCSR04.hpp"
#include "4_drivers/pico_pwm/pico_pwm.hpp"

namespace orchestration {

struct Drivers
{
	drivers::Ssd1306  screen;
	drivers::RTC_HW84 rtc;
	drivers::HCSR04   prox;
	drivers::pico_pwm led;

	static constexpr uint8_t PIN_LED          = 22;
	static constexpr uint8_t PIN_PROX_TRIG    = 26;
	static constexpr uint8_t PIN_PROX_ECHO    = 27;
	static constexpr uint8_t DISTANCE_LIMITE  = 80;

	Drivers(i2c_inst_t *i2c)
		: screen(i2c), rtc(i2c), prox(PIN_PROX_TRIG, PIN_PROX_ECHO, DISTANCE_LIMITE), led(PIN_LED)
	{}
};

}
