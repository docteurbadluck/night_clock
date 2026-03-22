#pragma once

namespace interface
{

class ProxDetector
{
public:
	virtual ~ProxDetector() = default;
	virtual bool	triggered() = 0;
};

}