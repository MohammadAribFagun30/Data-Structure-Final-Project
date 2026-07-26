@echo off
echo ============================================
echo SORTING PROJECT - BUILD AND RUN
echo ============================================

echo.
echo Compiling experiments...
g++ -std=c++17 -Wall -O2 -o experiments.exe sorting_experiments.cpp
if %errorlevel% neq 0 (
    echo ERROR: Compilation failed!
    pause
    exit /b %errorlevel%
)

echo Compiling bonus...
g++ -std=c++17 -Wall -O2 -o bonus.exe adversarial_bonus.cpp
if %errorlevel% neq 0 (
    echo ERROR: Compilation failed!
    pause
    exit /b %errorlevel%
)

echo.
echo Running experiments...
experiments.exe

echo.
echo Running bonus...
bonus.exe

echo.
echo Generating visualizations...
python analysis.py

echo.
echo ============================================
echo COMPLETE! Check output files.
echo ============================================
pause