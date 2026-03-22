#include "1_domain/Context/Context.hpp"
#include <string>
#include "internal/internal.hpp"

extern "C"
{
	#include "unity.h"

	void setUp(void) {}
	void tearDown(void) {}
}


int main(void)
{
	UNITY_BEGIN();
	test_time();
	test_night();
	RUN_TEST(test_day);
	return UNITY_END();
}
