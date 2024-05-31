#include "Logger/src/ThreadSafeLogger/logger_ThreadSafeLogger.h"
#include "Context/src/Context/context_Context.h"
#include "Logger/src/Processor/logger_mock_Processor.h"
#include "Logger/src/Processor/logger_stub_Processor.h"

#include <future>
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

namespace logger
{

using Promise = std::promise<ThreadSafeLogger::RetCode>;
using Future = std::future<ThreadSafeLogger::RetCode>;
using Promises = std::vector<Promise>;
using Futures = std::vector<Future>;
using Results = std::vector<ThreadSafeLogger::RetCode>;

class ThreadSafeLoggerTest : public testing::Test
{
protected:
	stub::Processor m_stubProcessor;
	mock::Processor m_mockProcessor{&m_stubProcessor};

	Context m_context;

	static constexpr context::Id k_id = context::k_maxId - 10;
	context::Context m_idContext{k_id};

	ThreadSafeLogger m_sut{m_context, m_mockProcessor};

	static void Calculate(Promise& promise, ThreadSafeLogger& sut, context::Context& idContext);
	static void WaitFutures(Futures& futures, Results& results);
};

TEST_F(ThreadSafeLoggerTest, Multithreading)
{
	constexpr size_t k_threadsCount = 20;

	Promises promises(k_threadsCount);
	Futures futures(k_threadsCount);
	Results results;

	std::transform(promises.begin(), //
				   promises.end(),
				   futures.begin(),
				   [](Promise& x) -> Future { return x.get_future(); });

	m_context.WaitAttempt();
	ASSERT_EQ(Context::State::k_waitAttempt, m_context.GetState());
	m_mockProcessor.ExpectInvokeAnyTimes();

	std::vector<std::thread> threads(k_threadsCount);
	for(size_t i = 0; i < k_threadsCount; i++)
	{
		threads[i] = std::thread(Calculate, //
								 std::ref(promises[i]),
								 std::ref(m_sut),
								 std::ref(m_idContext));
	}
	std::thread waitThread(WaitFutures, //
						   std::ref(futures),
						   std::ref(results));

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	m_stubProcessor.ReturnTrueOnce();

	for(auto& t : threads)
	{
		t.join();
	}
	waitThread.join();

	ASSERT_EQ(k_threadsCount, results.size());

	bool hasOnlyOneOk = 1 == std::count(results.begin(), //
										results.end(),
										ThreadSafeLogger::RetCode::k_ok);
	bool alreadyFinishedOther =
		results.size() - 1 == std::count(results.begin(), //
										 results.end(),
										 ThreadSafeLogger::RetCode::k_alreadyFinished);

	ASSERT_TRUE(hasOnlyOneOk);
	ASSERT_TRUE(alreadyFinishedOther);
}

TEST_F(ThreadSafeLoggerTest, WaitAttempt)
{
	ASSERT_EQ(Context::State::k_idle, m_context.GetState());

	const auto res = m_sut.Invoke(m_idContext);

	ASSERT_EQ(ThreadSafeLogger::RetCode::k_waitAttempt, res);
}

TEST_F(ThreadSafeLoggerTest, WaitAttemptThenOkThenAlreadyFinished)
{
	constexpr size_t k_waitAttemptAttempts = 10;
	constexpr size_t k_okAttemptsCount = 1;
	constexpr size_t k_alreadyFinishedAttempts = 10;
	constexpr size_t k_attempts = k_waitAttemptAttempts + //
								  k_okAttemptsCount + //
								  k_alreadyFinishedAttempts;

	for(size_t attempt = 0; attempt < k_attempts; attempt++)
	{
		const bool isWaitAttempt = k_waitAttemptAttempts > attempt;
		const bool isOkAttempt = !isWaitAttempt && //
								 k_waitAttemptAttempts + k_okAttemptsCount > attempt;
		if(isOkAttempt)
		{
			m_context.WaitAttempt();
			ASSERT_EQ(Context::State::k_waitAttempt, m_context.GetState());

			m_stubProcessor.ReturnTrueOnce();
			m_mockProcessor.ExpectInvoke();
		}

		const auto res = m_sut.Invoke(m_idContext);

		const auto expectedRes = isWaitAttempt ? ThreadSafeLogger::RetCode::k_waitAttempt
								 : isOkAttempt ? ThreadSafeLogger::RetCode::k_ok
											   : ThreadSafeLogger::RetCode::k_alreadyFinished;

		ASSERT_EQ(expectedRes, res);
	}
}

void ThreadSafeLoggerTest::Calculate(Promise& promise,
									 ThreadSafeLogger& sut,
									 context::Context& idContext)
{
	ThreadSafeLogger::RetCode res = ThreadSafeLogger::RetCode::k_noFiles;

	while(1)
	{
		try
		{
			res = sut.Invoke(idContext);
		}
		catch(...)
		{
			promise.set_exception(std::current_exception());
			return;
		}
		if(ThreadSafeLogger::RetCode::k_ok == res ||
		   ThreadSafeLogger::RetCode::k_alreadyFinished == res)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	promise.set_value(res);
}

void ThreadSafeLoggerTest::WaitFutures(Futures& futures, Results& results)
{
	results.clear();
	for(auto& result : results)
	{
		result = ThreadSafeLogger::RetCode::k_busy;
	}
	for(auto& future : futures)
	{
		try
		{
			const auto res = future.get();
			results.push_back(res);
		}
		catch(...)
		{
			continue;
		}
	}
}

} // namespace logger
