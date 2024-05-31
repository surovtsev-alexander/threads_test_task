#include "Exceptions/src/CustomException/exceptions_CustomException.h"

#include <stdio.h>

namespace systemTools
{

class FileGuard final
{
public:
	FileGuard(const char* fileName);
	~FileGuard();

	FILE* GetFile();
private:
	FILE* m_file;
};

inline FileGuard::FileGuard(const char* fileName)
{
	m_file = fopen(fileName, "a");
}

inline FileGuard::~FileGuard()
{
	if(!m_file)
	{
		return;
	}

	(void)fclose(m_file);
}

inline FILE* FileGuard::GetFile()
{
	return m_file;
}

} // namespace systemTools
