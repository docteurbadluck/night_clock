#include "2_usecases/DetectProx/DetectProx.hpp"

extern "C"
{
	#include "unity.h"

	void setUp(void) {}
	void tearDown(void) {}
}

class MockProxDetector : public interface::ProxDetector
{
	public:
	bool motion = false;
	bool triggered() override { return motion;};
};

void test_detect_prox(void)
{
	domain::Context ctx;
	MockProxDetector prox_detector;
	usecases::DetectProx detectProx(prox_detector);
	prox_detector.motion = true;

	TEST_ASSERT_FALSE(ctx.getMovementDetected());
	detectProx.updateDetectedState(ctx);
	TEST_ASSERT_TRUE(ctx.getMovementDetected());
}

void test_no_motion(void)
{
	domain::Context ctx;
	MockProxDetector prox_detector;
	usecases::DetectProx detectProx(prox_detector);
	prox_detector.motion = false;

	detectProx.updateDetectedState(ctx);
	TEST_ASSERT_FALSE(ctx.getMovementDetected());
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_detect_prox);
	RUN_TEST(test_no_motion);

	return UNITY_END();
}
