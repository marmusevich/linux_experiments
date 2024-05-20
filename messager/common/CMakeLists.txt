##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
cmake_path(SET CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# [2024-03] try static - it doesn't work
set(VCPKG_LIBRARY_LINKAGE "static" CACHE STRING "")

##############################################################################
project(commonLib VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##############################################################################
set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost REQUIRED )  
if (Boost_FOUND)
   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif ()
##############################################################################

##############################################################################
FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")
#gropped sourse file in IDE by path	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})

add_library(common STATIC ${sources} ${headers})

target_include_directories(common 
	PUBLIC 
		${Boost_INCLUDE_DIRS}
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

#target_link_libraries(common
#	PRIVATE  
#        Boost::log
#)
	
###########################################################	
add_subdirectory(test)