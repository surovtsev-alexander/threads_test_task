#pragma once

#include "Context/src/context_Types.h"

namespace context
{
class Context final
{
public:
	Context(Id id);
	~Context();

	uint64_t GetId() const;

private:
	const Id m_id;
};

inline Id Context::GetId() const
{
	return m_id;
}

} // namespace context
