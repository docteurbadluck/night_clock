#pragma once
#include "string"
#include "internal/Time/Time.hpp"

namespace domain
{

enum State
{
	SLEEPY,
	READY,
	ACTIVE
};


class Context
{
	private :
		State	state;
		bool	movement_detected;

		Time	current_time;
		Time	night_start;
		Time	night_end;
		bool	isNight();
		bool	test_button_pressed;
		bool	action_finished;

		void	compute_sleepy_state();
		void	compute_ready_state();
		void	compute_active_state();
	
	public :
		Context();
		Context(std::string current_time,
			std::string night_start,
			std::string night_end);
		~Context() = default;

		void		computeState();
		void		setInput(bool test_button_state, bool movement_sensor_state);
		void		setFinishAction(bool action_state);
		void		setCurrentTime(const std::string &current_time);
		void		setMovementDetected(bool movement_sensor_state);
		State		getState() const;
		bool		getMovementDetected() const;
		bool		getActionFinished() const;

		std::string	getCurrentTime() const;

};

}