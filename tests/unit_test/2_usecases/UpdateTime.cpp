#include "2_usecases/UpdateTime/UpdateTime.hpp"

extern "C"
{
	#include "unity.h"

	void setUp(void) {}
	void tearDown(void) {}
}

class MockClock : public interface::Clock
{
	public:
	std::string current_time = "10:10:00";
	std::string getCurrentTime() override { return current_time;};
};

void test_update_time(void)
{
	domain::Context ctx;
	MockClock clock;
	usecases::UpdateTime update_time(clock);
	clock.current_time = "10:10:00";

	TEST_ASSERT_EQUAL_STRING("10:00:00", ctx.getCurrentTime().c_str());
	update_time.updateCurrentTime(ctx);
	TEST_ASSERT_EQUAL_STRING("10:10:00", ctx.getCurrentTime().c_str());
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_update_time);

	return UNITY_END();
}
