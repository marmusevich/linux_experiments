##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
cmake_path(SET CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

##############################################################################
project(messager VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##############################################################################
set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost REQUIRED )  
if (Boost_FOUND)
   include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
   
   message("Boost VERSION: ${Boost_VERSION}")
   message("Boost INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
   message("Boost Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
   message("Boost LIBRARIES: ${Boost_LIBRARIES}")   
endif ()


##############################################################################
cmake_path(SET SHARED_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../shared)
add_subdirectory(${SHARED_LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/shared)

cmake_path(SET COMMON_LIB_PATH common)
add_subdirectory(${COMMON_LIB_PATH})

add_subdirectory(server)
add_subdirectory(client)
