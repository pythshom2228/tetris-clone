#pragma once
#include <vector>
#include <random>
#include "Tetramino.hpp"

class Field {
public:

    Field(const Vector2& position, std::size_t width, std::size_t height);

    void update();
    void render() const;
    void setComplexity(std::size_t complexity);
    void moveTetraminoRight();
    void moveTetraminoLeft();
    void moveTetraminoDown();
    void dropTetramino();
    void rotateTetramino();
    bool isGameOver();

    Vector2     getPosition(); 
    std::size_t getWidth() const;
    std::size_t getHeight() const;
    std::size_t getScore();

private:

    void moveDown(std::size_t emptyRow);
    void clearRows();   
    void resetTetramino();

private:

    static constexpr std::size_t tetraminosCount = 7;

    std::vector<std::vector<TetrisCube>> matrix;
    Tetramino currentTetramino;
    std::size_t score;

    std::mt19937 mrd;
    std::uniform_int_distribution<int> randomDist;

};
