#pragma once

#include "Context/src/Context/context_Context.h"
#include "Logger/src/ThreadSafeLogger/logger_IThreadSafeLogger.h"
#include "SystemTools/src/TimeManager/systemTools_ITimeManager.h"

#include <random>
#include <windows.h>

namespace logger
{

class Task final
{
public:
	Task(const context::Context& idContext,
		 IThreadSafeLogger& threadSafeLogger,
		 systemTools::ITimeManager& timeManager);
	~Task();

	void Invoke();
	void Sleep();

	enum class DelayMs : DWORD
	{
		k_2Sec = 2'000,
		k_4Sec = 4'000,
	};

private:
	const context::Context& m_idContext;
	IThreadSafeLogger& m_threadSafeLogger;
	systemTools::ITimeManager& m_timeManager;
};

} // namespace logger
