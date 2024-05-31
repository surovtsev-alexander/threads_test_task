#include "context_IdGenerator.h"

#include "Context/src/Checker/context_Checker.h"
#include "Exceptions/src/CustomException/exceptions_CustomException.h"

#include <memory>
#include <random>
#include <stdint.h>

namespace context
{

Id IdGenerator::GenerateRandomID()
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<Id> distribution(k_minId, k_maxId);
	return distribution(generator);
}

Id* IdGenerator::GenetateIds(size_t count) throw(exceptions::CustomException)
{
	auto res = std::make_unique<Id[]>(count);

	for(size_t i = 0; i < count; i++)
	{
		bool failed = true;
		for(size_t attempt = 0; attempt < k_maxAttemptsToGenerateUniqueId; attempt++)
		{
			res[i] = GenerateRandomID();
			if(!Checker::AreTheyInMinMaxRange(res.get() + i, 1))
			{
				continue;
			}
			if(Checker::IsThereNoRepetiotions(res.get(), i))
			{
				failed = false;
				break;
			}
		}
		if(failed)
		{
			throw exceptions::CustomException(
				(std::string("Exceeded attempts when generating ") + std::to_string(i + 1))
					.c_str());
		}
	}

	return res.release();
}

} // namespace context
