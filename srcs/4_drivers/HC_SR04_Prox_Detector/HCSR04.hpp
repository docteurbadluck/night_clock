#include "3_interface/ProxDetector.hpp"
#include <stdint.h>

namespace drivers 
{

class HCSR04 : public interface::ProxDetector
{
	private:
		uint8_t	_pin_trig;
		uint8_t	_pin_echo;
		uint8_t	_distance_cm;

		void		trig();
		uint64_t	getEchoTime();
		uint32_t	timeToDistanceCm(uint64_t pulseDurationUs) const;

	public :
		HCSR04(uint8_t pin_trig, uint8_t pin_echo, uint8_t distance_cm);
		~HCSR04() = default;
		bool	triggered() override;
		bool	selfTest() override;
};

}