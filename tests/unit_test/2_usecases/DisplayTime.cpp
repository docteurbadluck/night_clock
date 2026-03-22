#include "2_usecases/DisplayTime/DisplayTime.hpp"

extern "C"
{
	#include "unity.h"

	void setUp(void) {}
	void tearDown(void) {}
}

class MockScreen : public interface::Screen
{
public:
	std::string last_displayed = "";
	void display(const std::string &time) override { last_displayed = time; }
};

void test_display_time(void)
{
	domain::Context ctx;
	MockScreen screen;
	usecases::DisplayTime display_time(screen);

	ctx.setCurrentTime("09:05:03");
	display_time.displayCurrentTime(ctx);

	TEST_ASSERT_EQUAL_STRING("09:05:03", screen.last_displayed.c_str());
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_display_time);

	return UNITY_END();
}
