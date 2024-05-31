set(
	UNIT_TESTS_FILES

	${COMPONENTS_DIR}/Context/unit_tests/ContextChecker/context_ContextCheckerTest.cpp
	${COMPONENTS_DIR}/Context/unit_tests/IdGenerator/context_IdGeneratorTest.cpp

	${COMPONENTS_DIR}/Logger/src/Processor/logger_mock_Processor.h
	${COMPONENTS_DIR}/Logger/src/Processor/logger_stub_Processor.cpp
	${COMPONENTS_DIR}/Logger/src/Processor/logger_stub_Processor.h

	${COMPONENTS_DIR}/Logger/src/ThreadSafeLogger/logger_mock_ThreadSafeLogger.h

	${COMPONENTS_DIR}/Logger/unit_tests/ThreadSafeLogger/logger_ThreadSafeLoggerTest.cpp
	${COMPONENTS_DIR}/Logger/unit_tests/Task/logger_TaskTest.cpp
	${COMPONENTS_DIR}/Logger/unit_tests/Processor/logger_ProcessorTest.cpp

	${COMPONENTS_DIR}/SystemTools/src/Threads/systemTools_mock_Thread.h
	${COMPONENTS_DIR}/SystemTools/src/Threads/systemTools_stub_Thread.cpp
	${COMPONENTS_DIR}/SystemTools/src/Threads/systemTools_stub_Thread.h
	${COMPONENTS_DIR}/SystemTools/src/TimeManager/systemTools_mock_TimeManager.h
	
	${COMPONENTS_DIR}/SystemTools/unit_tests/Threads/systemTools_win_ThreadTest.cpp
	${COMPONENTS_DIR}/SystemTools/unit_tests/ThreadsHelper/systemTools_ThreadsHelperTest.cpp
)
