@echo off
cls

rem to first run only
::setx VCPKG_ROOT "d:\cpp\vcpkg" >nul
::setx PATH "%PATH%;%VCPKG_ROOT%" >nul

echo VCPKG_ROOT is '%VCPKG_ROOT%'

setlocal enabledelayedexpansion

set BuildDir=_ms_build

rem for debug cmake file
::rd /s /q %BuildDir%

mkdir %BuildDir%
cmake -G "Visual Studio 17" -B %BuildDir% "-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
cmake --build %BuildDir%

pause