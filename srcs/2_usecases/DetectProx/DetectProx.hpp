#include "1_domain/Context/Context.hpp"
#include "3_interface/ProxDetector.hpp"

namespace usecases {

class DetectProx
{
private:
	interface::ProxDetector &proxDetector;

public:
	DetectProx(interface::ProxDetector &proxDetector);
	~DetectProx() = default;
	void	updateDetectedState(domain::Context &ctx);
};

}