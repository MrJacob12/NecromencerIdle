@echo off
cls
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
gcc main.c storage.c ^
    ui/ui.c ui/texture.c ui/text.c ui/position.c ui/button.c ui/scene.c ^
    utils/number_format.c ^
    -I%LIBPATH%SDL3\include -I%LIBPATH%SDL3_ttf\include ^
    -L%LIBPATH%SDL3\lib -L%LIBPATH%SDL3_ttf\lib ^
    -I%LIBPATH%SDL3_image\include -L%LIBPATH%SDL3_image\lib  ^
    logic\target\x86_64-pc-windows-gnu\release\liblogic.a ^
    -lSDL3 -lSDL3_ttf -lSDL3_image -lws2_32 ^
    -mwindows -o build/NecromancerIdle.exe >> log.txt
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