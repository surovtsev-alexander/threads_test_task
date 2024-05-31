set(
	COMPONENTS_FILES

	${COMPONENTS_DIR}/Context/src/Checker/context_Checker.cpp
	${COMPONENTS_DIR}/Context/src/Checker/context_Checker.h
	${COMPONENTS_DIR}/Context/src/Context/context_Context.cpp
	${COMPONENTS_DIR}/Context/src/Context/context_Context.h
	${COMPONENTS_DIR}/Context/src/IdGenerator/context_IdGenerator.cpp
	${COMPONENTS_DIR}/Context/src/IdGenerator/context_IdGenerator.h
	${COMPONENTS_DIR}/Context/src/context_Types.h

	${COMPONENTS_DIR}/Exceptions/src/CustomException/exceptions_CustomException.h

	${COMPONENTS_DIR}/Logger/src/Context/logger_Context.cpp
	${COMPONENTS_DIR}/Logger/src/Context/logger_Context.h
	${COMPONENTS_DIR}/Logger/src/Processor/logger_IProcessor.h
	${COMPONENTS_DIR}/Logger/src/Processor/logger_Processor.cpp
	${COMPONENTS_DIR}/Logger/src/Processor/logger_Processor.h
	${COMPONENTS_DIR}/Logger/src/Task/logger_Task.cpp
	${COMPONENTS_DIR}/Logger/src/Task/logger_Task.h
	${COMPONENTS_DIR}/Logger/src/ThreadSafeLogger/logger_IThreadSafeLogger.h
	${COMPONENTS_DIR}/Logger/src/ThreadSafeLogger/logger_ThreadSafeLogger.cpp
	${COMPONENTS_DIR}/Logger/src/ThreadSafeLogger/logger_ThreadSafeLogger.h

	${COMPONENTS_DIR}/SystemTools/src/FileGuard/systemTools_FileGuard.h
	${COMPONENTS_DIR}/SystemTools/src/FilesystemHelper/systemTools_FilesystemHelper.cpp
	${COMPONENTS_DIR}/SystemTools/src/FilesystemHelper/systemTools_FilesystemHelper.h
	${COMPONENTS_DIR}/SystemTools/src/TracerRAII/systemTools_TracerRAII.h
	${COMPONENTS_DIR}/SystemTools/src/Threads/systemTools_IThread.h
	${COMPONENTS_DIR}/SystemTools/src/Threads/systemTools_win_Thread.cpp
	${COMPONENTS_DIR}/SystemTools/src/Threads/systemTools_win_Thread.h
	${COMPONENTS_DIR}/SystemTools/src/ThreadsHelper/systemTools_ThreadsHelper.cpp
	${COMPONENTS_DIR}/SystemTools/src/ThreadsHelper/systemTools_ThreadsHelper.h
	${COMPONENTS_DIR}/SystemTools/src/TimeManager/systemTools_ITimeManager.h
	${COMPONENTS_DIR}/SystemTools/src/TimeManager/systemTools_TimeManager.cpp
	${COMPONENTS_DIR}/SystemTools/src/TimeManager/systemTools_TimeManager.h
	${COMPONENTS_DIR}/SystemTools/src/TracerRAII/systemTools_TracerRAII.h
)
