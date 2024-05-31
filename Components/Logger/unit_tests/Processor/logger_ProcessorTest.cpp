#include "Logger/src/Processor/logger_Processor.h"
#include "SystemTools/src/FilesystemHelper/systemTools_FilesystemHelper.h"

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

namespace logger
{

class ProcessorTest : public testing::Test
{
protected:
	static constexpr context::Id k_id = context::k_minId + 10;
	context::Context m_idContext{k_id};

	Processor m_sut{Processor::k_logFileName};

	void ExamineLogFile(const char* logFileName, //
						const std::vector<std::string>& testFileNames,
						bool& outRes) const;
	static void CreateFile(const char* fileName);
	static void DeleteFolderAndContents(const char* folderName);
};

class TestFolderGuard final
{
public:
	TestFolderGuard(const char* folderName, bool silent)
		: m_folderName(folderName)
		, m_silent(silent)
	{
		m_createCalled = false;
	}
	~TestFolderGuard()
	{
		if(!m_createCalled)
		{
			return;
		}
		auto status = rmdir(m_folderName);
	}

	void Create()
	{
		m_createCalled = true;
		const auto status = mkdir(m_folderName);
		if(!m_silent)
		{
			ASSERT_EQ(EXIT_SUCCESS, status);
		}
	}

private:
	const char* const m_folderName;
	const bool m_silent;
	bool m_createCalled = false;
};

TEST_F(ProcessorTest, Main)
{
	constexpr char k_testFolderName[] = "test_folder";

	DeleteFolderAndContents(k_testFolderName);

	TestFolderGuard folderGuard(k_testFolderName, true);
	folderGuard.Create();

	{
		const auto res = _chdir(k_testFolderName);
		ASSERT_FALSE(res);
		if(res)
		{
			return;
		}
	}

	const std::vector<std::string> k_testFileNames = {
		"a.txt",
		"2123.txt",
		"123.x",
		"124.5",
	};

	for(const auto& testFileName : k_testFileNames)
	{
		CreateFile(testFileName.c_str());
	}

	auto res = m_sut.Invoke(m_idContext);
	ASSERT_EQ(IProcessor::RetCode::k_ok, res);

	{
		bool res = false;
		ExamineLogFile(Processor::k_logFileName, k_testFileNames, res);
		ASSERT_TRUE(res);
	}

	{
		const auto res = systemTools::FilesystemHelper::TryToRemoveFile(Processor::k_logFileName);
		ASSERT_EQ(EXIT_SUCCESS, res);
	}

	{
		std::vector<std::string> restFilesInFolder;

		{
			const auto res =
				systemTools::FilesystemHelper::GetAllFilesInWorkingDir(restFilesInFolder);
			ASSERT_EQ(EXIT_SUCCESS, res);
		}

		for(auto& file : restFilesInFolder)
		{
			const auto res = systemTools::FilesystemHelper::IsFileNameWithsWith(
				file.c_str(), Processor::k_fileEnding);
			ASSERT_FALSE(res);
		}

		for(auto testFileName : k_testFileNames)
		{
			if(!systemTools::FilesystemHelper::IsFileNameWithsWith(testFileName.c_str(),
																   Processor::k_fileEnding))
			{
				const auto it = std::find(restFilesInFolder.begin(), //
										  restFilesInFolder.end(),
										  testFileName);
				ASSERT_NE(restFilesInFolder.end(), it);
			}
		}

		for(auto& restFileInFolder : restFilesInFolder)
		{
			if(EXIT_SUCCESS != systemTools::FilesystemHelper::TryToRemoveFile( //
								   restFileInFolder.c_str()))
			{
				ASSERT_TRUE(false);
			}
		}
	}

	{
		const auto res = _chdir("..");
		ASSERT_FALSE(res);
	}
}

void ProcessorTest::ExamineLogFile(const char* logFileName, //
								   const std::vector<std::string>& testFileNames,
								   bool& outRes) const
{
	outRes = true;

	std::ifstream logFile(logFileName);
	if(!logFile.is_open())
	{
		ASSERT_TRUE(false);
		outRes = false;
		return;
	}

	uint64_t id = 0;

	logFile >> id;

	if(m_idContext.GetId() != id)
	{
		outRes = false;
		ASSERT_TRUE(false);
		return;
	}

	std::vector<std::string> namesInLogFile;

	while(!logFile.eof())
	{
		std::string fileName;
		std::getline(logFile, fileName);
		if(fileName.empty())
		{
			continue;
		}
		namesInLogFile.push_back(fileName);
	}

	for(auto& nameInLogFile : namesInLogFile)
	{
		const auto it = std::find(testFileNames.begin(), //
								  testFileNames.end(),
								  nameInLogFile);

		if(testFileNames.end() == it)
		{
			outRes = false;
			ASSERT_TRUE(false);
			return;
		}
	}

	for(auto& testFileName : testFileNames)
	{
		if(!systemTools::FilesystemHelper::IsFileNameWithsWith(testFileName.c_str(), //
															   Processor::k_fileEnding))
		{
			continue;
		}

		const auto it = std::find(namesInLogFile.begin(), //
								  namesInLogFile.end(),
								  testFileName);
		if(namesInLogFile.end() == it)
		{
			outRes = false;
			ASSERT_TRUE(false);
			return;
		}
	}

	outRes = true;
}

void ProcessorTest::CreateFile(const char* fileName)
{
	const auto f = fopen(fileName, "w");
	ASSERT_TRUE(f);
	if(f)
	{
		const auto res = fclose(f);
		ASSERT_FALSE(res);
	}
}

void ProcessorTest::DeleteFolderAndContents(const char* folderName)
{
	TestFolderGuard folderGuard(folderName, true);
	folderGuard.Create();

	{
		const auto res = _chdir(folderName);
		ASSERT_FALSE(res);
		if(res)
		{
			return;
		}
	}

	{
		std::vector<std::string> filesInFolder;
		{
			const auto res = systemTools::FilesystemHelper::GetAllFilesInWorkingDir(filesInFolder);
			ASSERT_EQ(EXIT_SUCCESS, res);
		}
		for(const auto& fileInFolder : filesInFolder)
		{
			const auto res = systemTools::FilesystemHelper::TryToRemoveFile(fileInFolder.c_str());
			ASSERT_EQ(EXIT_SUCCESS, res);
		}
	}

	{
		const auto res = _chdir("..");
		ASSERT_FALSE(res);
	}
}

} // namespace logger
