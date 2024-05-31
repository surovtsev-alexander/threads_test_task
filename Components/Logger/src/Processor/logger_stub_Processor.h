#pragma once

#include "logger_IProcessor.h"

#include <atomic>
#include <mutex>

namespace logger
{
namespace stub
{

class Processor final : public IProcessor
{
public:
	Processor() = default;
	~Processor() = default;

	RetCode Invoke(const context::Context& context) override;

	void ReturnTrueOnce();

private:
	bool m_returnTrueOnce = false;
	std::mutex m_mutex;
	std::atomic<int> m_atomic = 0;
};

inline void Processor::ReturnTrueOnce()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_returnTrueOnce = true;
}

} // namespace stub
} // namespace logger
