#include "SystemTools/src/Threads/systemTools_win_Thread.h"

#include <gtest/gtest.h>
#include <memory>
#include <windows.h>

namespace systemTools
{
namespace win
{

DWORD WINAPI InfinityThreadIfNotNullArg(LPVOID lpParam);

enum class DelayMs : DWORD
{
	k_1Sec = 1000,
};

TEST(WinThreadTest, CreateThreadThenWait)
{
	Thread thread(InfinityThreadIfNotNullArg, nullptr);
	thread.Create();
	const bool created = thread.IsCreated();
	ASSERT_TRUE(created);

	const bool finished = thread.IsFinished(IThread::WaitMs::k_100Ms);
	ASSERT_TRUE(finished);

	const bool closed = thread.Terminate();
	ASSERT_TRUE(closed);
}

TEST(WinThreadTest, TerminateThread)
{
	bool arg = true;
	Thread thread(InfinityThreadIfNotNullArg, &arg);
	thread.Create();

	const bool created = thread.IsCreated();
	ASSERT_TRUE(created);

	const bool finished = thread.IsFinished(IThread::WaitMs::k_100Ms);
	ASSERT_FALSE(finished);

	const bool terminationRes = thread.Terminate();
	ASSERT_TRUE(terminationRes);

	const bool finished2 = thread.IsFinished(IThread::WaitMs::k_100Ms);
	ASSERT_TRUE(finished2);

	const bool closed = thread.CloseHandle();
	ASSERT_TRUE(closed);
}

DWORD WINAPI InfinityThreadIfNotNullArg(LPVOID lpParam)
{
	if(!lpParam)
	{
		ExitThread(EXIT_SUCCESS);
	}

	for(;;)
	{
		Sleep(100);
	}

	ExitThread(EXIT_SUCCESS);
}

} // namespace win
} // namespace systemTools
