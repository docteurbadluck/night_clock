#include "2_usecases/StartLight/StartLight.hpp"

extern "C"
{
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}
}

// --- Mock ---

class MockPWM : public interface::PWM
{
public:
	float last_duty = 0.0f;
	void  apply_duty(float intensity) override { last_duty = intensity; }
};

// --- Helpers ---

static void set_active(domain::Context &ctx)
{
	ctx.setInput(false, true, false);
	ctx.computeState();
}

// StartLight(pwm, rise_s, fix_s, fall_s, max_intensity, period_ms)
//
// With period_ms = 500 and 1s durations:
//   rise_steps = 1000 / 500 = 2   =>  step = 0.8 / 2 = 0.4
//   fix_ticks  = 1000 / 500 = 2   =>  3 ticks in FIX (decrement x2 then transition)
//   fall_steps = 2000 / 500 = 4   =>  step = 0.8 / 4 = 0.2
//
// Full tick sequence to OFF (9 ticks):
//   1: OFF -> RISING (intensity=0.0)
//   2: RISING intensity=0.4
//   3: RISING intensity=0.8 -> FIX (remaining=2)
//   4: FIX remaining=1
//   5: FIX remaining=0 -> FALLING (intensity unchanged)
//   6: FALLING intensity=0.6
//   7: FALLING intensity=0.4
//   8: FALLING intensity=0.2
//   9: FALLING intensity=0.0 -> OFF

static usecases::StartLight make_light(MockPWM &pwm)
{
	return usecases::StartLight(pwm,
	                            /*rise_s=*/1, /*fix_s=*/1, /*fall_s=*/2,
	                            /*max_intensity=*/0.8f, /*period_ms=*/500);
}

// --- Tests ---

void test_initial_state_is_off(void)
{
	MockPWM              pwm;
	domain::Context      ctx;
	usecases::StartLight light = make_light(pwm);

	TEST_ASSERT_EQUAL(usecases::OFF, light.getPwmState().state);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, light.getPwmState().current_intensity);
}

void test_first_tick_transitions_to_rising(void)
{
	MockPWM              pwm;
	domain::Context      ctx;
	usecases::StartLight light = make_light(pwm);

	set_active(ctx);
	light.tick(ctx);

	TEST_ASSERT_EQUAL(usecases::RISING, light.getPwmState().state);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, light.getPwmState().current_intensity);
}

void test_rising_increments_duty_each_tick(void)
{
	MockPWM              pwm;
	domain::Context      ctx;
	usecases::StartLight light = make_light(pwm);

	set_active(ctx);
	light.tick(ctx); // OFF -> RISING (duty stays 0)
	light.tick(ctx); // step 1: +0.4
	TEST_ASSERT_EQUAL_FLOAT(0.4f, light.getPwmState().current_intensity);
	light.tick(ctx); // step 2: +0.4 => reaches max
	TEST_ASSERT_EQUAL_FLOAT(0.8f, light.getPwmState().current_intensity);
}

void test_fix_holds_max_duty(void)
{
	MockPWM              pwm;
	domain::Context      ctx;
	usecases::StartLight light = make_light(pwm);

	set_active(ctx);
	light.tick(ctx); // -> RISING
	light.tick(ctx);
	light.tick(ctx); // -> FIX

	TEST_ASSERT_EQUAL(usecases::FIX, light.getPwmState().state);
	light.tick(ctx);
	TEST_ASSERT_EQUAL_FLOAT(0.8f, light.getPwmState().current_intensity);
	light.tick(ctx);
	TEST_ASSERT_EQUAL_FLOAT(0.8f, light.getPwmState().current_intensity);
}

void test_falling_decrements_duty_each_tick(void)
{
	MockPWM              pwm;
	domain::Context      ctx;
	usecases::StartLight light = make_light(pwm);

	set_active(ctx);
	light.tick(ctx); // tick 1: -> RISING
	light.tick(ctx); // tick 2: duty=40
	light.tick(ctx); // tick 3: duty=80 -> FIX (remaining=2)
	light.tick(ctx); // tick 4: FIX remaining=1
	light.tick(ctx); // tick 5: FIX remaining=0 -> FALLING

	TEST_ASSERT_EQUAL(usecases::FALLING, light.getPwmState().state);
	TEST_ASSERT_EQUAL_FLOAT(0.8f, light.getPwmState().current_intensity);

	light.tick(ctx);
	TEST_ASSERT_EQUAL_FLOAT(0.6f, light.getPwmState().current_intensity);
	light.tick(ctx);
	TEST_ASSERT_EQUAL_FLOAT(0.4f, light.getPwmState().current_intensity);
	light.tick(ctx);
	TEST_ASSERT_EQUAL_FLOAT(0.2f, light.getPwmState().current_intensity);
	light.tick(ctx);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, light.getPwmState().current_intensity);
}

void test_off_after_falling_signals_action_finished(void)
{
	MockPWM              pwm;
	domain::Context      ctx;
	usecases::StartLight light = make_light(pwm);

	set_active(ctx);
	light.tick(ctx); // tick 1: -> RISING
	light.tick(ctx); // tick 2: duty=40
	light.tick(ctx); // tick 3: duty=80 -> FIX
	light.tick(ctx); // tick 4: FIX remaining=1
	light.tick(ctx); // tick 5: FIX remaining=0 -> FALLING
	light.tick(ctx); // tick 6: duty=60
	light.tick(ctx); // tick 7: duty=40
	light.tick(ctx); // tick 8: duty=20
	light.tick(ctx); // tick 9: duty=0 -> OFF

	TEST_ASSERT_EQUAL(usecases::OFF, light.getPwmState().state);
	TEST_ASSERT_TRUE(ctx.getActionFinished());
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_initial_state_is_off);
	RUN_TEST(test_first_tick_transitions_to_rising);
	RUN_TEST(test_rising_increments_duty_each_tick);
	RUN_TEST(test_fix_holds_max_duty);
	RUN_TEST(test_falling_decrements_duty_each_tick);
	RUN_TEST(test_off_after_falling_signals_action_finished);
	return UNITY_END();
}
