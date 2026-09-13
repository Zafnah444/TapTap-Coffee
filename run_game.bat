@echo off
echo Building Tap Tap Coffee...
gcc taptap_coffee.c -o taptap_coffee.exe -I include -L lib -lraylib -lgdi32 -lwinmm -lm -lpthread

if %errorlevel% neq 0 (
    echo.
    echo Build FAILED. Scroll up to see the error.
    pause
    exit /b
)

echo Build succeeded! Launching...
taptap_coffee.exe
