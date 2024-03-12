#!/bin/bash

export VCPKG_ROOT="~/vcpkg"

# set path in case script runs outside contained dir
cd "$(dirname "$0")"

BuildDir="Build"

# for debug cmake file
rm -r  $BuildDir

mkdir $BuildDir
cmake -B $BuildDir 
# later a coverage move to cmake file
# -DCMAKE_CXX_FLAGS=--coverage -DCMAKE_CXX_FLAGS=-pg

cmake --build $BuildDir