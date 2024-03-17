##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
cmake_path(SET CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# [2024-03] try static - it doesn't work
set(VCPKG_LIBRARY_LINKAGE "static" CACHE STRING "")

##############################################################################

project(shared VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##############################################################################
set(Boost_NO_WARN_NEW_VERSIONS 1)
# [2024-03] try static - it doesn't work
#set(Boost_USE_STATIC_LIBS ON)
##set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED COMPONENTS 
	program_options
#    log_setup
    log
)  
if (Boost_FOUND)
   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
   
   message("Boost VERSION: ${Boost_VERSION}")
   message("Boost INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
   message("Boost Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
   message("Boost LIBRARIES: ${Boost_LIBRARIES}")   
endif ()
##############################################################################

FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")
add_library(sharedLib STATIC ${sources} ${headers})

target_include_directories(sharedLib 
	PUBLIC 
		${Boost_INCLUDE_DIRS}
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(sharedLib
	PRIVATE  
		Boost::program_options
#        Boost::log_setup
        Boost::log
)

#gropped sourse file in IDE by path	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})
	
