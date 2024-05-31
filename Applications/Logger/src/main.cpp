#include <stdlib.h>

#include "Context/src/IdGenerator/context_IdGenerator.h"
#include "Exceptions/src/CustomException/exceptions_CustomException.h"
#include "Logger/src/Processor/logger_Processor.h"
#include "Logger/src/Task/logger_Task.h"
#include "Logger/src/ThreadSafeLogger/logger_ThreadSafeLogger.h"
#include "SystemTools/src/Threads/systemTools_win_Thread.h"
#include "SystemTools/src/ThreadsHelper/systemTools_ThreadsHelper.h"
#include "SystemTools/src/TimeManager/systemTools_TimeManager.h"

#include <iostream>
#include <memory>

static void Invoke();

int main()
{
	try
	{
		Invoke();
	}
	catch(exceptions::CustomException ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}
	catch(std::exception ex)
	{
		std::cout << "Unexpected error: " << ex.what() << std::endl;
	}
	return EXIT_SUCCESS;
}

static void Invoke()
{
	constexpr size_t k_threadsCount = 2;

	auto ids = std::unique_ptr<context::Id[]>(context::IdGenerator::GenetateIds(k_threadsCount));

	const context::Context idContext1{ids[0]};
	const context::Context idContext2{ids[1]};

	logger::Context loggerContext;
	logger::Processor loggerProcessor{logger::Processor::k_logFileName};
	logger::ThreadSafeLogger threadSafeLogger{loggerContext, loggerProcessor};
	systemTools::TimeManager timeManager;
	logger::Task task1{idContext1, threadSafeLogger, timeManager};
	logger::Task task2{idContext2, threadSafeLogger, timeManager};

	systemTools::win::Thread thread1(task1);
	systemTools::win::Thread thread2(task2);

	loggerContext.WaitAttempt();

	const std::vector<systemTools::IThread*> threads = {&thread1, &thread2};

	systemTools::ThreadsHelper::LaunchAllAndWaitOneFinishedThread(threads);
}
