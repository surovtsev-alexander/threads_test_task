#pragma once

#include "systemTools_IThread.h"
#include <gmock/gmock.h>

namespace systemTools
{
namespace mock
{

class Thread final : public IThread
{
public:
	Thread(IThread* stub)
		: m_stub(stub)
	{
		if(!m_stub)
		{
			return;
		}

		ON_CALL(*this, Create).WillByDefault(testing::Invoke(m_stub, &IThread::Create));
		ON_CALL(*this, IsCreated).WillByDefault(testing::Invoke(m_stub, &IThread::IsCreated));
		ON_CALL(*this, IsFinished).WillByDefault(testing::Invoke(m_stub, &IThread::IsFinished));
		ON_CALL(*this, Terminate).WillByDefault(testing::Invoke(m_stub, &IThread::Terminate));
		ON_CALL(*this, CloseHandle).WillByDefault(testing::Invoke(m_stub, &IThread::CloseHandle));
	}

	~Thread() = default;

	MOCK_METHOD(void, Create, (), (override));
	MOCK_METHOD(bool, IsCreated, (), (const override));
	MOCK_METHOD(bool, IsFinished, (WaitMs waitMs), (const override));
	MOCK_METHOD(bool, Terminate, (), (override));
	MOCK_METHOD(bool, CloseHandle, (), (override));

	void ExpectCreateOnce()
	{
		EXPECT_CALL(*this, Create).Times(1);
	}

	void ExpectIsFinishedAnyTimes()
	{
		EXPECT_CALL(*this, IsFinished).Times(testing::AnyNumber());
	}

private:
	IThread* const m_stub;
};

} // namespace mock
} // namespace systemTools
