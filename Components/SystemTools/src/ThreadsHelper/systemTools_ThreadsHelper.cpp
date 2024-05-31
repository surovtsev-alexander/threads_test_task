#include "systemTools_ThreadsHelper.h"

namespace systemTools
{

void ThreadsHelper::LaunchAllAndWaitOneFinishedThread(const std::vector<IThread*>& threads)
{
	for(auto* const thread : threads)
	{
		if(!thread)
		{
			continue;
		}
		thread->Create();
	}
	for(;;)
	{
		for(const auto* const thread : threads)
		{
			if(!thread)
			{
				continue;
			}
			if(thread->IsFinished(IThread::WaitMs::k_10Ms))
			{
				return;
			}
		}
	}
}

} // namespace systemTools
