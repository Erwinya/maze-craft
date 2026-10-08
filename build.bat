@echo off
setlocal
where g++ >nul 2>&1
if errorlevel 1 (
  echo g++ not found. Install LLVM-MinGW or MSYS2, then re-run build.bat
  exit /b 1
)
if not exist build mkdir build
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude src\main.cpp src\maze.cpp -o build\maze-craft.exe
if errorlevel 1 exit /b 1
echo Built build\maze-craft.exe
echo Example: build\maze-craft.exe --width 21 --height 11 --seed 7 --svg build\maze.svg
endlocal
