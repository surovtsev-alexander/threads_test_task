#pragma once

#include <stdbool.h>
#include <stdint.h>

namespace logger
{

class Context final
{
public:
	Context() = default;
	~Context() = default;

	enum class State : size_t
	{
		k_idle,
		k_waitAttempt,
		k_done,
	};

	void WaitAttempt();
	void Done();
	State GetState() const;

private:
	State m_state = State::k_idle;
};

inline void Context::WaitAttempt()
{
	m_state = State::k_waitAttempt;
}

inline void Context::Done()
{
	m_state = State::k_done;
}

inline Context::State Context::GetState() const
{
	return m_state;
}

} // namespace logger
