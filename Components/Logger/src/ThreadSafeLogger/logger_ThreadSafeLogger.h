#pragma once

#include "logger_IThreadSafeLogger.h"

#include "Logger/src/Context/logger_Context.h"
#include "Logger/src/Processor/logger_IProcessor.h"

#include <mutex>

namespace logger
{

class ThreadSafeLogger final: public IThreadSafeLogger
{
public:
	ThreadSafeLogger(Context& context, IProcessor& processor);
	~ThreadSafeLogger();

	RetCode Invoke(const context::Context& context) override;

private:
	Context& m_context;
	IProcessor& m_processor;
	std::mutex m_mutex;
};

} // namespace logger
