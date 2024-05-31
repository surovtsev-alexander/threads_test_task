#pragma once

#include "Context/src/Context/context_Context.h"

namespace logger
{

class IProcessor
{
public:
	IProcessor() = default;
	virtual ~IProcessor() = default;

	enum class RetCode : size_t
	{
		k_ok = 0,
		k_noFiles = 1,
		k_failedToOpenLogFile,
		k_errorWhileListingFiles,
		k_errorWhileWritingToLogFile,
	};

	virtual RetCode Invoke(const context::Context& context) = 0;
};

} // namespace logger
