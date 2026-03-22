#include "1_domain/Context/Context.hpp"
#include "internal.hpp"
#include <string>

extern "C"
{
	#include "unity.h"
}

void test_compute_state(void)
{
	domain::Context context(std::string("10:10:10"), std::string("21:00:00"), std::string("06:00:00"));
	TEST_ASSERT_EQUAL_INT(domain::SLEEPY, context.getState());
}

void test_end_of_night(void)
{
	domain::Context context(std::string("06:00:01"), std::string("21:00:00"), std::string("06:00:00"));
	TEST_ASSERT_EQUAL_INT(domain::SLEEPY, context.getState());
}

void test_beginning_of_night(void)
{
	domain::Context context(std::string("21:00:01"), std::string("21:00:00"), std::string("06:00:00"));
	TEST_ASSERT_EQUAL_INT(domain::READY, context.getState());
}

void test_time(void)
{
	RUN_TEST(test_compute_state);
	RUN_TEST(test_end_of_night);
	RUN_TEST(test_beginning_of_night);
}
