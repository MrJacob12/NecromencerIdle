@echo off
REM Build Rust library (staticlib)
cd logic
cargo clean
cargo build --release --target x86_64-pc-windows-gnu
if errorlevel 1 (
    echo Rust build failed!
    exit /b 1
)
cd ..

REM Set up environment for GCC
set LIBPATH=D:\lib\

REM Compile code
gcc main.c ^
    -I%LIBPATH%SDL3\include -I%LIBPATH%SDL3_ttf\include ^
    -L%LIBPATH%SDL3\lib -L%LIBPATH%SDL3_ttf\lib ^
    logic\target\x86_64-pc-windows-gnu\release\liblogic.a ^
    -lSDL3 -lSDL3_ttf -lws2_32 ^
    -o build/NecromancerIdle.exe >> log.txt
if errorlevel 1 (
    echo GCC build failed!
    exit /b 1
)

echo Build succeeded!
cd build
REM Run the executable
NecromancerIdle.exe
if errorlevel 1 (
    echo Program execution failed!
    exit /b 1
)
cd ..