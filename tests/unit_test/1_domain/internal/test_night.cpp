#include "1_domain/Context/Context.hpp"
#include "internal.hpp"
#include <string>

extern "C"
{
	#include "unity.h"
}

// Button is ignored during night
void test_night_button_ignored(void)
{
	domain::Context context(std::string("21:00:01"), std::string("21:00:00"), std::string("06:00:00"));
	context.setInput(true, false);
	context.computeState();
	TEST_ASSERT_EQUAL_INT(domain::READY, context.getState());
}

// Sensor triggers ACTIVE during night
void test_night_sensor_to_active(void)
{
	domain::Context context(std::string("21:00:01"), std::string("21:00:00"), std::string("06:00:00"));
	context.setInput(false, true);
	context.computeState();
	TEST_ASSERT_EQUAL_INT(domain::ACTIVE, context.getState());
}

// Finishing action returns to READY
void test_night_active_to_ready(void)
{
	domain::Context context(std::string("21:00:01"), std::string("21:00:00"), std::string("06:00:00"));
	context.setInput(false, true);
	context.computeState();

	context.setInput(false, false);
	context.setFinishAction(true);
	context.computeState();
	context.setFinishAction(false);
	TEST_ASSERT_EQUAL_INT(domain::READY, context.getState());
}


void test_night(void)
{
	RUN_TEST(test_night_button_ignored);
	RUN_TEST(test_night_sensor_to_active);
	RUN_TEST(test_night_active_to_ready);
}
