#include "logger_stub_Processor.h"

#include <Exceptions/src/CustomException/exceptions_CustomException.h>

namespace logger
{
namespace stub
{

IProcessor::RetCode Processor::Invoke(const context::Context& context)
{
	m_atomic++;

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	if(m_atomic > 1)
	{
		throw exceptions::CustomException("Called from more than one thread simultaneously");
	}

	if(!m_returnTrueOnce)
	{
		m_atomic--;

		return RetCode::k_noFiles;
	}

	std::lock_guard<std::mutex> lock(m_mutex);

	m_returnTrueOnce = false;

	m_atomic--;

	return RetCode::k_ok;
}

} // namespace stub
} // namespace logger
