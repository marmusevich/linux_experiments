##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(boost_misc VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost REQUIRED
	COMPONENTS program_options
	# TODO  set concrete libs that needed
)  

if (Boost_FOUND)
   message(STATUS "           Boost version: ${Boost_VERSION} !!!")
   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif ()


##############################################################################

FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")

add_executable(boost_misc ${sources} ${headers})

target_include_directories(boost_misc 
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
	)


target_link_libraries(boost_misc
  PRIVATE  
  ${Boost_LIBRARIES}
  #boost_program_options
)
	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})
	

add_custom_command(
	TARGET boost_misc POST_BUILD
#    OUTPUT out file or may mark SYMBOLIC
    COMMAND boost_misc -h
#    DEPENDS any/dependency.file
    COMMENT "try run"
    VERBATIM
)
