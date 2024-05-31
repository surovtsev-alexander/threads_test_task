#include "logger_ThreadSafeLogger.h"

namespace logger
{

ThreadSafeLogger::ThreadSafeLogger(Context& context, IProcessor& processor)
	: m_context(context)
	, m_processor(processor)
{ }

ThreadSafeLogger::~ThreadSafeLogger() { }

ThreadSafeLogger::RetCode ThreadSafeLogger::Invoke(const context::Context& context)
{
	std::unique_lock<std::mutex> lock(m_mutex, std::try_to_lock);
	if(!lock.owns_lock())
	{
		return RetCode::k_busy;
	}

	const auto state = m_context.GetState();
	if(Context::State::k_idle == state)
	{
		return RetCode::k_waitAttempt;
	}
	if(Context::State::k_done == state)
	{
		return RetCode::k_alreadyFinished;
	}

	const IProcessor::RetCode processed = m_processor.Invoke(context);
	if(IProcessor::RetCode::k_noFiles == processed)
	{
		return RetCode::k_noFiles;
	}
	if (IProcessor::RetCode::k_ok == processed)
	{
		m_context.Done();
		return RetCode::k_ok;
	}

	m_context.Done();
	return RetCode::k_errorWhileWriting;
}

} // namespace logger
