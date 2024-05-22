##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
cmake_path(SET CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

##############################################################################
project(messager_client VERSION 0.1.0 LANGUAGES CXX)

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

FILE(GLOB_RECURSE headers "include/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")
#gropped sourse file in IDE by path	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})


##############################################################################
add_executable(client ${sources} ${headers})

# Fix: error LNK2038: mismatch detected for 'boost_log_abi': value 'v2_mt_nt6' doesn't match value 'v2_mt_nt62'
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_definitions(client 
		PRIVATE
			-D_WIN32_WINNT=0x0602
	)
endif()


target_include_directories(client 
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${SHARED_LIB_PATH}/include
		${COMMON_LIB_PATH}/include
)

target_link_libraries(client
	PRIVATE  
		sharedLib
		common
)

