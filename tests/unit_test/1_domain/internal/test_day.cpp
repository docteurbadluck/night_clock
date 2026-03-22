#include "1_domain/Context/Context.hpp"
#include "internal.hpp"
#include <string>

extern "C"
{
	#include "unity.h"
}

void test_day(void)
{
	domain::Context context(std::string("10:00:01"), std::string("21:00:00"), std::string("06:00:00"));
	TEST_ASSERT_EQUAL_INT(domain::SLEEPY, context.getState());

	context.setInput(true, false);
	context.computeState();
	TEST_ASSERT_EQUAL_INT(domain::ACTIVE, context.getState());
	context.setFinishAction(true);
	context.setInput(false, false);
	context.computeState();
	TEST_ASSERT_EQUAL_INT(domain::SLEEPY, context.getState());
}
