@echo off
cls

setx VCPKG_ROOT "d:\cpp\vcpkg" >nul
setx PATH "%PATH%;%VCPKG_ROOT%" >nul

echo VCPKG_ROOT is '%VCPKG_ROOT%'

setlocal enabledelayedexpansion

:: set path in case script runs outside contained dir
cd %~dp0

set BuildDir=%~dp0Build

rem for debug cmake file
rd /s /q %BuildDir%

mkdir %BuildDir%
cmake -G "Visual Studio 17" -B %BuildDir% 
cmake --build %BuildDir%

pause
