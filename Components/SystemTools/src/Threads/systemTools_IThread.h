#pragma once

#include <windows.h>

namespace systemTools
{

class IThread
{
public:
	enum class WaitMs : DWORD
	{
		k_10Ms = 10,
		k_100Ms = 100,
	};

	IThread() = default;
	virtual ~IThread() = default;

	virtual void Create() = 0;
	virtual bool IsCreated() const = 0;
	virtual bool IsFinished(WaitMs waitMs) const = 0;
	virtual bool Terminate() = 0;
	virtual bool CloseHandle() = 0;
};

} // namespace systemTools
