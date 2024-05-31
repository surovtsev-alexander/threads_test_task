#pragma once

#include <exception>
#include <string>

namespace exceptions
{

class CustomException final : public std::exception
{
public:
	CustomException(const char* message) throw()
		: std::exception(message)
	{ }
};

} // namespace exceptions
