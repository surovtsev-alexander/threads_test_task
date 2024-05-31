#include "Context/src/Checker/context_Checker.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

namespace context
{
struct Param
{
	std::vector<Id> values;
	bool isThereNoRepetition;
	bool areTheyInMinMaxRange;
};

class ContextCheckerTest : public testing::TestWithParam<Param>
{ };

TEST_P(ContextCheckerTest, IsThereNoRepetiotions)
{
	const auto& param = GetParam();

	const bool res = Checker::IsThereNoRepetiotions(param.values.data(), //
													param.values.size());
	ASSERT_EQ(res, param.isThereNoRepetition);
}

TEST_P(ContextCheckerTest, AreTheyInMinMaxRange)
{
	const auto& param = GetParam();

	const bool res = Checker::AreTheyInMinMaxRange(param.values.data(), //
												   param.values.size());
	ASSERT_EQ(res, param.areTheyInMinMaxRange);
}

const Param k_params[] = {
	{
		{10, 11, 12, 123213},
		true,
		false,
	},
	{
		{10, 11, 12, 124, 15, 124, 16},
		false,
		false,
	},
	{
		{},
		true,
		true,
	},
	{
		{UINT64_MAX - 100, UINT64_MAX - 50, UINT64_MAX - 100},
		false,
		true,
	},
	{
		{UINT64_MAX - 10, UINT64_MAX - 1},
		true,
		true,
	},
};

INSTANTIATE_TEST_SUITE_P(context, ContextCheckerTest, testing::ValuesIn(k_params));

} // namespace context
