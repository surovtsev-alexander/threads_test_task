#pragma once

#include <cstdlib>
#include <string>
#include <vector>
#include <functional>

namespace systemTools
{

class FilesystemHelper final
{
public:
	using FileNameCallBack = std::function<void(const char* fileName)>;

	static int IterateFilesInWorkingDir(FileNameCallBack fileNameCallback);
	static int GetAllFilesInWorkingDir(std::vector<std::string>& files);
	static int TryToRemoveFile(const char* fileName);
	static bool IsFileNameWithsWith(const char* fileName, const char* expectedEnd);

private:
	FilesystemHelper() = delete;
};

} // namespace systemTools
