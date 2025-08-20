#pragma once
#include "Textures.hpp"
#include <stdexcept>

Texture TetrisTextures::cubeTexture = {.id=0};

void TetrisTextures::load() {
    cubeTexture = LoadTexture("../resources/texture.png");
    if(cubeTexture.id == 0)
        throw std::runtime_error("Cube Texture not Found");
}
