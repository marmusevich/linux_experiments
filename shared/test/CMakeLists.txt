##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(shared_test LANGUAGES CXX)


##############################################################################
find_package(GTest REQUIRED)

enable_testing()	
include(GoogleTest)
##############################################################################

FILE(GLOB_RECURSE tests "*.cpp")
add_executable(shared_test
  ${tests}
)

target_include_directories(shared_test
	PRIVATE 
		../include
)


target_link_libraries(shared_test
	PRIVATE
		GTest::GTest
		GTest::gtest_main

		sharedLib
)

#gtest_discover_tests(shared_test)	

#add_test(shared_gtests shared_test)
	
