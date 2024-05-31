#pragma once

#include "logger_IThreadSafeLogger.h"

#include <gmock/gmock.h>

namespace logger
{
namespace mock
{

class ThreadSafeLogger final : public IThreadSafeLogger
{
public:
	ThreadSafeLogger() { }

	~ThreadSafeLogger() { }

	MOCK_METHOD(RetCode, Invoke, (const context::Context& context), (override));
};

} // namespace mock
} // namespace logger
