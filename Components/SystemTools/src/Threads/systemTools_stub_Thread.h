#pragma once

#include "systemTools_IThread.h"

namespace systemTools
{
namespace stub
{

class Thread final : public IThread
{
public:
	Thread();
	~Thread();

	void Create() override;
	bool IsCreated() const override;
	bool IsFinished(WaitMs waitMs) const override;
	bool Terminate() override;
	bool CloseHandle() override;

	void SetFinished();

private:
	enum class State : size_t
	{
		k_noThread = 0,
		k_created,
		k_finished,
	};
	State m_state = State::k_noThread;
};

inline void Thread::SetFinished()
{
	m_state = State::k_finished;
}

} // namespace stub
} // namespace systemTools
