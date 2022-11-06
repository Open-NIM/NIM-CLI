cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(NIM_CLI VERSION 0.1 DESCRIPTION "CLI software for the NIM modules interface." HOMEPAGE_URL "https://github.com/Open-NIM" LANGUAGES CXX)

set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	SET(GCC_FLAGS "-Wall -g -pedantic -pedantic-errors -ansi -Wextra -Weffc++ -std=c++20 -O0")
	add_definitions(${GCC_FLAGS})
endif()

add_subdirectory(libNIM)
add_subdirectory(src)
add_executable(NIMCLI src/main.cpp)
target_include_directories(NIMCLI PUBLIC libNIM/include include)
target_link_libraries(NIMCLI PUBLIC serial NIM NIMCLIlibs)
