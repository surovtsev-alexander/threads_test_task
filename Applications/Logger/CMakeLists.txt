cmake_minimum_required(VERSION 3.5)

project(Logger LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (MSVC)
    add_compile_options(/W4)
	set(CMAKE_CXX_FLAGS -EHsc)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
	set(CMAKE_CXX_EXTENSIONS ON)
endif()

set(REPO_ROOT_DIR ${CMAKE_SOURCE_DIR}/../..)
set(COMPONENTS_DIR ${REPO_ROOT_DIR}/components)
set(THIRD_PARTY_DIR ${REPO_ROOT_DIR}/thirdParty)

include(scripts/components.cmake)

set(
	SOURCES

	${COMPONENTS_FILES}
	${UNIT_TESTS_FILES}
	
	src/main.cpp
)

include_directories(
	PRIVATE ${COMPONENTS_DIR}
	PRIVATE ${THIRD_PARTY_DIR}/
)

add_executable(
	${CMAKE_PROJECT_NAME}

	${SOURCES}
)
