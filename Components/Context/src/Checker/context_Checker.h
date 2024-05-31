#pragma once

#include "Context/src/Context/context_Context.h"

namespace context
{

class Checker final
{
public:
	static bool IsThereNoRepetiotions(const Id* arr, size_t len);
	static bool AreTheyInMinMaxRange(const Id* arr, size_t len);

private:
	Checker() = delete;
};

} // namespace context
