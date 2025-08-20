#include "Game.hpp"
#include "Textures.hpp"
#include <exception>
#include <iostream>
#include <raylib.h>

int main() {

    SetConfigFlags(FLAG_VSYNC_HINT);
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800,800,"Tetris");
    
    try {
        TetrisTextures::load();
    } catch(const std::exception& ex) {
        std::cout << ex.what();
    }

    Game Tetris;

    Tetris.run();

    return 0;
}
