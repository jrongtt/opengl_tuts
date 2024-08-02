@echo off
cd /d "%~dp0"
if not exist build (
    mkdir build
)
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/jackp/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
if %errorlevel% neq 0 exit /b %errorlevel%
cd Debug
if exist ModernOpenGL.exe (
    start ModernOpenGL.exe
) else (
    echo "Executable not found"
)
