#pragma once
#include "Field.hpp"
#include <memory>

enum class GameState  {
    Active,
    Pause
};

class Game {
public:

    Game();

    void run(); 

private:  

    void handleActiveInput();
    void handlePauseInput();

    void update();

    void render() const;

private:
    mutable GameState currentState;
    mutable std::unique_ptr<Field> map;
    std::size_t totalScore;
       
};
