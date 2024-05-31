#pragma once

#include "Context/src/Context/context_Context.h"

namespace logger
{

class IThreadSafeLogger
{
public:
	IThreadSafeLogger() = default;
	~IThreadSafeLogger() = default;

	enum class RetCode : size_t
	{
		k_ok = 0,
		k_busy,
		k_waitAttempt,
		k_alreadyFinished,
		k_errorWhileWriting,
		k_noFiles,
	};

	virtual RetCode Invoke(const context::Context& context) = 0;
};

} // namespace logger
