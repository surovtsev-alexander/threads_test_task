#include "systemTools_stub_Thread.h"

namespace systemTools
{
namespace stub
{

Thread::Thread() { }

Thread::~Thread() { }

void Thread::Create()
{
	if(State::k_noThread == m_state)
	{
		m_state = State::k_created;
	}
}

bool Thread::IsCreated() const
{
	return State::k_created == m_state;
}

bool Thread::IsFinished(WaitMs waitMs) const
{
	return !IsCreated();
}

bool Thread::Terminate()
{
	m_state = State::k_finished;
	return true;
}

bool Thread::CloseHandle()
{
	m_state = State::k_noThread;
	return true;
}

} // namespace stub
} // namespace systemTools
