#include "logger_Task.h"

#include <memory>
#include <random>
#include <stdint.h>
#include <windows.h>

namespace logger
{

Task::Task(const context::Context& idContext,
		   IThreadSafeLogger& threadSafeLogger,
		   systemTools::ITimeManager& timeManager)
	: m_idContext(idContext)
	, m_threadSafeLogger(threadSafeLogger)
	, m_timeManager(timeManager)
{ }

Task::~Task() { }

void Task::Invoke()
{
	for(;;)
	{
		Sleep();

		const auto res = m_threadSafeLogger.Invoke(m_idContext);

		//printf("%llu: %lu\n", m_idContext.GetId(), res);

		if(IThreadSafeLogger::RetCode::k_busy == res || //
		   IThreadSafeLogger::RetCode::k_waitAttempt == res ||
		   IThreadSafeLogger::RetCode::k_noFiles == res)
		{
			continue;
		}

		break;
	}
}

void Task::Sleep()
{
	m_timeManager.RandomSleep(static_cast<DWORD>(DelayMs::k_2Sec),
							  static_cast<DWORD>(DelayMs::k_4Sec));
}

} // namespace logger
