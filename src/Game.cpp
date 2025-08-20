#include <memory>
#include <raylib.h>
#include "Game.hpp"

Game::Game()
:   currentState(GameState::Active),
    map(std::make_unique<Field>(Vector2{10,10},10,20)),
    totalScore(map->getScore()) {

    SetExitKey(KEY_NULL);
}


void Game::run() {
    
    while(!WindowShouldClose()) {
        this->update();
        this->render();
    }

    CloseWindow();
}


void Game::update() {
    
    switch(currentState) {
        case GameState::Active: {
              this->handleActiveInput(); 
              this->map->update(); 
              this->totalScore = map->getScore();
              break;
        }
        case GameState::Pause: {
            this->handlePauseInput();
            break;
        }
    }
    
}

void Game::render() const {
    BeginDrawing();
    ClearBackground(Color{255,255,255,0});
        
    this->map->render();

    DrawText(
            std::to_string(this->totalScore).c_str(),
            this->map->getPosition().x + float(this->map->getWidth() - 1) / 2,
            this->map->getPosition().y - 32,
            32,
            BLACK
        );
    if(currentState == GameState::Pause) {
        int screenWidth = GetScreenWidth(); 
        int screenHeight = GetScreenHeight();
        DrawRectangle(0,0,screenWidth,screenHeight,Color{128,128,128,128});
        screenHeight = screenWidth /  2 - 100;
        screenWidth = screenHeight / 2 + 100;
        DrawRectangle(screenWidth, screenHeight,300,200,BLUE);
        Rectangle restartButton = {
                float(screenWidth),
                float(screenHeight) + 50,
                300,
                100
        };
        Color textColor = WHITE;
        if(CheckCollisionPointRec(GetMousePosition(),restartButton)) {
            textColor = GRAY; 
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                this->map = std::make_unique<Field>(Vector2{10,10},10,20);
                this->currentState = GameState::Active;
            }
        }
        DrawText("Restart",restartButton.x + 20,restartButton.y + 10,64,textColor);
    }
    EndDrawing();
}


void Game::handleActiveInput() {
    if(IsKeyPressed(KEY_ESCAPE)) {
        this->currentState = GameState::Pause;
    }
    if(IsKeyDown(KEY_LEFT)) {
        this->map->moveTetraminoLeft();
    }
    if(IsKeyDown(KEY_RIGHT)) {
        this->map->moveTetraminoRight();
    }
    if(IsKeyDown(KEY_DOWN)) {
        this->map->moveTetraminoDown();
    }
    if(IsKeyPressed(KEY_UP)) {
        this->map->dropTetramino();
    }
    if(IsKeyPressed(KEY_R)) {
       this->map->rotateTetramino(); 
    }
    static int comp = 1;
    if(IsKeyPressed(KEY_E)) {
        this->map->setComplexity(30);
    }
    if(IsKeyPressed(KEY_D)) {
        this->map->setComplexity(1);
    }
}

void Game::handlePauseInput() {
    if(IsKeyPressed(KEY_ESCAPE)) {
        this->currentState = GameState::Active;
    }
}

