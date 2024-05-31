#include "systemTools_win_Thread.h"

namespace systemTools
{
namespace win
{

Thread::Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
	: m_lpStartAddress(lpStartAddress)
	, m_lpParameter(lpParameter)
{ }

Thread::Thread(logger::Task& task)
	: m_lpStartAddress(RunTask)
	, m_lpParameter(static_cast<LPVOID>(&task))
{ }

Thread::~Thread()
{
	(void)Terminate();
	(void)CloseHandle();
}

void Thread::Create()
{
	if(m_thread)
	{
		return;
	}
	m_thread = CreateThread(nullptr, 0, m_lpStartAddress, m_lpParameter, 0, nullptr);
	if(!m_thread)
	{
		throw exceptions::CustomException("thread is not created");
	}
}

bool Thread::IsCreated() const
{
	return m_thread;
}

bool Thread::IsFinished(WaitMs waitMs) const
{
	if(!m_thread)
	{
		return true;
	}
	const auto waitRes = WaitForSingleObject(m_thread, static_cast<DWORD>(waitMs));
	return WAIT_OBJECT_0 == waitRes;
}

bool Thread::Terminate()
{
	if(!m_thread)
	{
		return true;
	}
	if(IsFinished(WaitMs::k_10Ms))
	{
		return true;
	}
	return TerminateThread(m_thread, EXIT_SUCCESS);
}

bool Thread::CloseHandle()
{
	if(!m_thread)
	{
		return true;
	}
	const bool res = ::CloseHandle(m_thread);
	if(res)
	{
		m_thread = 0;
	}
	return res;
}

DWORD WINAPI Thread::RunTask(LPVOID lpParam)
{
	logger::Task* taks = static_cast<logger::Task*>(lpParam);

	taks->Invoke();

	return EXIT_SUCCESS;
}

} // namespace win
} // namespace systemTools
