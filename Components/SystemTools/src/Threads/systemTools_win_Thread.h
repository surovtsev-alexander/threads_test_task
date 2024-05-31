#pragma once

#include "systemTools_IThread.h"

#include "Exceptions/src/CustomException/exceptions_CustomException.h"
#include "Logger/src/Task/logger_Task.h"

#include <windows.h>

namespace systemTools
{
namespace win
{

class Thread final : public IThread
{
public:
	Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter);
	Thread(logger::Task& task);
	~Thread();

	void Create() override;
	bool IsCreated() const override;
	bool IsFinished(WaitMs waitMs) const override;
	bool Terminate() override;
	bool CloseHandle() override;

private:
	HANDLE m_thread = 0;
	const LPTHREAD_START_ROUTINE m_lpStartAddress;
	const LPVOID m_lpParameter;

	static DWORD WINAPI RunTask(LPVOID lpParam);
};

} // namespace win
} // namespace systemTools
