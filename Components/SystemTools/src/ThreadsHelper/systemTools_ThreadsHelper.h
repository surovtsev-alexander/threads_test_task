#pragma once

#include "SystemTools/src/Threads/systemTools_IThread.h"

#include <vector>

namespace systemTools
{

class ThreadsHelper final
{
public:
	static void LaunchAllAndWaitOneFinishedThread(const std::vector<IThread*>& threads);

private:
	ThreadsHelper() = delete;
};

} // namespace systemTools
