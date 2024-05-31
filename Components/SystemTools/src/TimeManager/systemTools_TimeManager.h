#pragma once

#include "systemTools_ITimeManager.h"

#include <random>

namespace systemTools
{

class TimeManager final: public ITimeManager
{
public:
	TimeManager();
	~TimeManager();

	void RandomSleep(DWORD minMs, DWORD maxMs) override;

private:
	std::random_device m_randomDevice;
	std::mt19937 m_generator{m_randomDevice()};
};

} // namespace systemTools
