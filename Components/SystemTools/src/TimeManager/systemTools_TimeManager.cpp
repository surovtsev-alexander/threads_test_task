#include "systemTools_TimeManager.h"

namespace systemTools
{

TimeManager::TimeManager() { }

TimeManager::~TimeManager() { }

void TimeManager::RandomSleep(DWORD minMs, DWORD maxMs)
{
	std::uniform_int_distribution<DWORD> distribution{minMs, maxMs};

	const DWORD delayMs = distribution(m_generator);

	::Sleep(delayMs);
}

} // namespace systemTools
