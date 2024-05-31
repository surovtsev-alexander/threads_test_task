#include "logger_Processor.h"

#include "SystemTools/src/FileGuard/systemTools_FileGuard.h"
#include "SystemTools/src/FilesystemHelper/systemTools_FilesystemHelper.h"

#include <windows.h>

namespace logger
{

Processor::Processor(const char* logFileName)
	: m_logFileName(logFileName)
{
	if(!logFileName)
	{
		throw exceptions::CustomException("logFileName is nullptr");
	}
}

Processor::~Processor() { }

class ResultCalculator
{
public:
	ResultCalculator(FILE& file, const context::Context& idContext)
		: m_file(file)
		, m_idContext(idContext)
	{ }
	~ResultCalculator() = default;

	void ProcessFileName(const char* fileName)
	{
		if(m_errorWhileWriting)
		{
			return;
		}
		if(!systemTools::FilesystemHelper::IsFileNameWithsWith(fileName, Processor::k_fileEnding))
		{
			return;
		}
		const auto res = systemTools::FilesystemHelper::TryToRemoveFile(fileName);
		if(EXIT_SUCCESS != res)
		{
			return;
		}
		if(!m_idWritten)
		{
			const int written = fprintf(&m_file, "%llu\n", m_idContext.GetId());
			if(written < 1)
			{
				m_errorWhileWriting = true;
				return;
			}
			m_idWritten = true;
		}
		const int written = fprintf(&m_file, "%s\n", fileName);
		if(written <= strlen(fileName))
		{
			m_errorWhileWriting = true;
		}
	}

	bool HasErrorWhileWriting() const
	{
		return m_errorWhileWriting;
	}

	bool IsIdWrittend() const
	{
		return m_idWritten;
	}

private:
	FILE& m_file;
	const context::Context& m_idContext;
	bool m_idWritten = false;
	bool m_errorWhileWriting = false;
};

Processor::RetCode Processor::Invoke(const context::Context& context)
{
	systemTools::FileGuard fileGuard(m_logFileName);
	FILE* const file = fileGuard.GetFile();
	if(!file)
	{
		return RetCode::k_failedToOpenLogFile;
	}
	ResultCalculator resultCalculator{*file, context};

	const auto res = systemTools::FilesystemHelper::IterateFilesInWorkingDir( //
		[&](const char* fileName) { //
			resultCalculator.ProcessFileName(fileName);
		});

	if(EXIT_SUCCESS != res)
	{
		return RetCode::k_errorWhileWritingToLogFile;
	}

	if(resultCalculator.HasErrorWhileWriting())
	{
		return RetCode::k_errorWhileWritingToLogFile;
	}

	if(!resultCalculator.IsIdWrittend())
	{
		return RetCode::k_noFiles;
	}

	return RetCode::k_ok;
}

} // namespace logger
