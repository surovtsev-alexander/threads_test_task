#include "Logger/src/Task/logger_Task.h"
#include "Logger/src/ThreadSafeLogger/logger_mock_ThreadSafeLogger.h"
#include "SystemTools/src/TimeManager/systemTools_mock_TimeManager.h"

#include <gtest/gtest.h>

namespace logger
{

class LoggerTaskTest : public testing::Test
{
protected:
	static constexpr size_t k_exitOnAttempt = 3;
	size_t m_attempts = 0;

	const context::Context m_idContext{context::k_minId + 1};
	mock::ThreadSafeLogger m_mockThreadSafeLogger;
	systemTools::mock::TimeManager m_mockTimeManager;
	Task m_task{m_idContext, m_mockThreadSafeLogger, m_mockTimeManager};

	void ExpectThreadSafeLoggerInvoke();
};

TEST_F(LoggerTaskTest, Main)
{
	EXPECT_CALL(m_mockTimeManager, RandomSleep).WillRepeatedly([](DWORD minMs, DWORD maxMs) {
		EXPECT_EQ(static_cast<DWORD>(Task::DelayMs::k_2Sec), minMs);
		EXPECT_EQ(static_cast<DWORD>(Task::DelayMs::k_4Sec), maxMs);
	});

	ExpectThreadSafeLoggerInvoke();

	m_task.Invoke();
}

void LoggerTaskTest::ExpectThreadSafeLoggerInvoke()
{
	EXPECT_CALL(m_mockThreadSafeLogger, Invoke)
		.WillOnce([&](const context::Context& context) -> IThreadSafeLogger::RetCode {
			if(m_attempts >= k_exitOnAttempt)
			{
				return IThreadSafeLogger::RetCode::k_ok;
			}
			m_attempts++;
			ExpectThreadSafeLoggerInvoke();

			return IThreadSafeLogger::RetCode::k_noFiles;
		});
}

} // namespace logger
