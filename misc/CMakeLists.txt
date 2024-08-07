##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
cmake_path(SET CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
##############################################################################

project(boost_misc VERSION 0.1.0 LANGUAGES CXX)


##############################################################################
#set(Boost_NO_WARN_NEW_VERSIONS 1)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_STATIC_RUNTIME ON)
#find_package(Boost REQUIRED
#	COMPONENTS 
#		boost_msm
#		
#)  
#if (Boost_FOUND)
#   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
#   
#   message("Boost VERSION: ${Boost_VERSION}")
#   message("Boost INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
#   message("Boost Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
#   message("Boost LIBRARIES: ${Boost_LIBRARIES}")   
#endif ()
##############################################################################




FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")
add_executable(misc ${sources} ${headers})

##############################################################################
cmake_path(SET SHARED_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../shared)
add_subdirectory(${SHARED_LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/shared)
##############################################################################

target_include_directories(misc 
	PRIVATE 
		${SHARED_LIB_PATH}/include
)

target_link_libraries(misc
	PRIVATE  
		sharedLib
#		Boost::msm
)


#gropped sourse file in IDE by path	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})
	
# ##############################################################################
# # execute APP
# add_custom_command(
	# TARGET misc POST_BUILD
# #    OUTPUT out file or may mark SYMBOLIC
    # COMMAND misc -h
# #    DEPENDS any/dependency.file
    # COMMENT "try run"
    # VERBATIM
# )
