#!/bin/bash

export VCPKG_ROOT="~/vcpkg"

BuildDir="Build"

# for debug cmake file
rm -r  $BuildDir

mkdir $BuildDir
cmake -B $BuildDir 
#"-DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
#cmake -B $BuildDir "-DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_CXX_FLAGS=--coverage -DCMAKE_CXX_FLAGS=-pg

cmake --build $BuildDir