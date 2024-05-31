#pragma once

#include "systemTools_ITimeManager.h"

#include <gmock/gmock.h>

namespace systemTools
{
namespace mock
{

class TimeManager final : public ITimeManager
{
public:
	TimeManager() = default;
	~TimeManager() = default;

	MOCK_METHOD(void, RandomSleep, (DWORD minMs, DWORD maxMs), (override));
};

} // namespace mock
} // namespace systemTools