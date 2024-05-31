#include "context_Checker.h"

namespace context
{

bool Checker::IsThereNoRepetiotions(const Id* arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
	{
		const Id a = arr[i];

		for(size_t j = i + 1; j < len; j++)
		{
			const Id b = arr[j];

			if(a == b)
			{
				return false;
			}
		}
	}

	return true;
}

bool Checker::AreTheyInMinMaxRange(const Id* arr, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		const Id val = arr[i];

		if (k_maxId < val || k_minId > val)
		{
			return false;
		}
	}

	return true;
}

} // namespace context
