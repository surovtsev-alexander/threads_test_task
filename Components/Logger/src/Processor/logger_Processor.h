#pragma once

#include "logger_IProcessor.h"

#include "Context/src/Context/context_Context.h"
#include "Exceptions/src/CustomException/exceptions_CustomException.h"

namespace logger
{

class Processor final : public IProcessor
{
public:
	Processor(const char* logFileName);
	~Processor();

	RetCode Invoke(const context::Context& context) override;

	static constexpr char k_logFileName[] = "list.log";
	static constexpr char k_fileEnding[] = ".txt";

private:
	const char* m_logFileName;
};

} // namespace logger
