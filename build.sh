set -e
clear

cd logic
cargo clean
cargo build --release --target aarch64-apple-darwin
cd ..

clang main.c storage.c \
    ui/ui.c ui/texture.c ui/text.c ui/position.c ui/button.c ui/scene.c \
    utils/number_format.c \
    -I/opt/homebrew/opt/sdl3/include \
    -I/opt/homebrew/opt/sdl3_ttf/include \
    -I/opt/homebrew/opt/sdl3_image/include \
    -L/opt/homebrew/opt/sdl3/lib \
    -L/opt/homebrew/opt/sdl3_ttf/lib \
    -L/opt/homebrew/opt/sdl3_image/lib \
    logic/target/aarch64-apple-darwin/release/liblogic.a \
    -lSDL3 -lSDL3_ttf -lSDL3_image \
    -o build/NecromancerIdle


echo "Build succeeded!"
cd build
./NecromancerIdle
cd ..