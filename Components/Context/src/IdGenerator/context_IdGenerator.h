#pragma once

#include "Context/src/context_Types.h"
#include "Exceptions/src/CustomException/exceptions_CustomException.h"

namespace context
{

class IdGenerator final
{
public:
	static Id GenerateRandomID();
	static Id* GenetateIds(size_t count) throw(exceptions::CustomException);

	static constexpr size_t k_maxAttemptsToGenerateUniqueId = 10;

private:
	IdGenerator() = delete;
};

} // namespace context
