#!/bin/bash

VCPKG_ROOT="~/vcpkg"
BuildDir="Build"

# for debug cmake file
rm -r  $BuildDir

mkdir $BuildDir
cmake -B $BuildDir "-DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build $BuildDir

