#pragma once

#include <windows.h>

namespace systemTools
{

class ITimeManager
{
public:
	ITimeManager() = default;
	~ITimeManager() = default;

	virtual void RandomSleep(DWORD minMs, DWORD maxMs) = 0;
};

} // namespace systemTools
