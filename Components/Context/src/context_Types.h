#pragma once

#include <stdint.h>

namespace context
{

using Id = uint64_t;

constexpr Id k_maxId = UINT64_MAX;
constexpr Id k_minId = UINT64_MAX / 10;

} // namespace context
