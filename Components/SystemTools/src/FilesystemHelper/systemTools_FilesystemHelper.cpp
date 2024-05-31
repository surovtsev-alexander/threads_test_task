#include "systemTools_FilesystemHelper.h"

#include <windows.h>

namespace systemTools
{

int FilesystemHelper::IterateFilesInWorkingDir(FileNameCallBack fileNameCallback)
{
	WIN32_FIND_DATA findFileData;
	HANDLE handle = FindFirstFile("./*", &findFileData);

	if(INVALID_HANDLE_VALUE == handle)
	{
		return EXIT_FAILURE;
	}

	do
	{
		if(FILE_ATTRIBUTE_DIRECTORY & findFileData.dwFileAttributes)
		{
			continue;
		}
		fileNameCallback(findFileData.cFileName);
	} while(FindNextFile(handle, &findFileData) != 0);

	return !FindClose(handle);
}

int FilesystemHelper::GetAllFilesInWorkingDir(std::vector<std::string>& files)
{
	files.clear();

	return FilesystemHelper::IterateFilesInWorkingDir(
		[&](auto fileName) { files.push_back(fileName); });
}

int FilesystemHelper::TryToRemoveFile(const char* fileName)
{
	return remove(fileName);
}

bool FilesystemHelper::IsFileNameWithsWith(const char* fileName, const char* expectedEnd)
{
	const size_t fileNameLen = strlen(fileName);
	const size_t expectedEndLen = strlen(expectedEnd);

	if(fileNameLen < expectedEndLen)
	{
		return false;
	}

	return !strcmp(fileName + fileNameLen - expectedEndLen, expectedEnd);
}

} // namespace systemTools
