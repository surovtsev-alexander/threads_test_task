#pragma once

#include <stdio.h>

namespace systemTools
{

class TracerRAII final
{
public:
	TracerRAII(const char* functionName);
	~TracerRAII();

private:
	const char* const m_functionName;
};

inline TracerRAII::TracerRAII(const char* functionName)
	: m_functionName(functionName)
{
	printf(">>%s\n", m_functionName);
}

inline TracerRAII::~TracerRAII()
{
	printf("<<%s\n", m_functionName);
}

} // namespace systemTools
