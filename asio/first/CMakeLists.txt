##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(boost_asio_first VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost REQUIRED)
if (Boost_FOUND)
   message(STATUS "           Boost version: ${Boost_VERSION} !!!")
   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif ()


##############################################################################

FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")

add_executable(boost_asio_first ${sources} ${headers})

target_include_directories(boost_asio_first 
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

#gropped sourse file in IDE by path	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})
