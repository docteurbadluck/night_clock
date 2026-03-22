#include "2_usecases/UpdateTime/UpdateTime.hpp"

namespace usecases {

UpdateTime::UpdateTime(interface::Clock &clock) : _clock(clock)
{
}
}