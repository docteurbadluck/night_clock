#include "2_usecases/DetectProx/DetectProx.hpp"

namespace usecases {

DetectProx::DetectProx(interface::ProxDetector &proxDetector) : proxDetector(proxDetector)
{
}
}