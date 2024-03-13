##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
cmake_path(SET CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# [2024-03] try static - it doesn't work
set(VCPKG_LIBRARY_LINKAGE "static" CACHE STRING "")

project(boost_misc VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(Boost_NO_WARN_NEW_VERSIONS 1)

# [2024-03] try static - it doesn't work
set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost REQUIRED COMPONENTS 
	program_options
)  

if (Boost_FOUND)
   message(STATUS "           Boost version: ${Boost_VERSION} !!!")
   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif ()

##############################################################################

FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")

add_executable(misc ${sources} ${headers})

target_include_directories(misc 
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(misc
	PRIVATE  
		Boost::program_options
)

#gropped sourse file in IDE by path	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})
	
##############################################################################
# execute APP
add_custom_command(
	TARGET misc POST_BUILD
#    OUTPUT out file or may mark SYMBOLIC
    COMMAND misc -h
#    DEPENDS any/dependency.file
    COMMENT "try run"
    VERBATIM
)


#The package gtest is compatible with built-in CMake targets:
#    enable_testing()
#    find_package(GTest CONFIG REQUIRED)
#    target_link_libraries(main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
#    add_test(AllTestsInMain main)
