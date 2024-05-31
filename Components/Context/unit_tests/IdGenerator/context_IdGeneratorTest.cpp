#include "Context/src/IdGenerator/context_IdGenerator.h"
#include "Context/src/Checker/context_Checker.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

namespace context
{

TEST(context_IdGeneratorTest, GenerateTwoIds)
{
	constexpr size_t k_attempts = 1000;
	for(size_t i = 0; i < k_attempts; i++)
	{
		constexpr size_t k_count = 2;
		auto ids = std::unique_ptr<Id[]>(IdGenerator::GenetateIds(k_count));
		ASSERT_NE(nullptr, ids.get());

		const bool checkingRes = Checker::IsThereNoRepetiotions(ids.get(), k_count) &&
								 Checker::AreTheyInMinMaxRange(ids.get(), k_count);

		ASSERT_TRUE(checkingRes);
	}
}

} // namespace context
