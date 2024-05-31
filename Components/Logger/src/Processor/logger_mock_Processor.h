#pragma once

#include "logger_IProcessor.h"

#include <gmock/gmock.h>

namespace logger
{
namespace mock
{
class Processor final : public IProcessor
{
public:
	Processor(IProcessor* stub)
		: m_stub(stub)
	{
		if(!m_stub)
		{
			return;
		}

		ON_CALL(*this, Invoke).WillByDefault(testing::Invoke(m_stub, &IProcessor::Invoke));
	}
	~Processor() = default;

	MOCK_METHOD(IProcessor::RetCode, Invoke, (const context::Context& context), (override));

	void ExpectInvoke()
	{
		EXPECT_CALL(*this, Invoke).Times(1);
	}

	void ExpectInvokeAnyTimes()
	{
		EXPECT_CALL(*this, Invoke).Times(testing::AnyNumber());
	}

private:
	IProcessor* const m_stub;
};
} // namespace mock
} // namespace logger
