#include "SystemTools/src/ThreadsHelper/systemTools_ThreadsHelper.h"
#include "SystemTools/src/Threads/systemTools_mock_Thread.h"
#include "SystemTools/src/Threads/systemTools_stub_Thread.h"

#include <future>
#include <gtest/gtest.h>
#include <memory>

namespace systemTools
{

struct TestSetup
{
	const std::vector<IThread*>& threads;
};

static void LaunchAndWaitDone(const TestSetup& setup);

TEST(ThreadsHelper, WaitOneFinishedThread)
{
	stub::Thread stubThread1;
	stub::Thread stubThread2;

	mock::Thread mockThread1{&stubThread1};
	mock::Thread mockThread2{&stubThread2};

	{
		testing::InSequence sequence;

		mockThread1.ExpectCreateOnce();
		mockThread1.ExpectIsFinishedAnyTimes();
	}
	{
		testing::InSequence sequence;

		mockThread2.ExpectCreateOnce();
		mockThread2.ExpectIsFinishedAnyTimes();
	}

	const std::vector<IThread*> threads = {&mockThread1, &mockThread2};

	TestSetup setup = {threads};

	std::thread testThread(LaunchAndWaitDone, std::ref(setup));

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	stubThread1.SetFinished();

	testThread.join();
}

static void LaunchAndWaitDone(const TestSetup& setup)
{
	ThreadsHelper::LaunchAllAndWaitOneFinishedThread(setup.threads);
}

} // namespace systemTools
