#include "Field.hpp"
#include "Tetramino.hpp"
#include <random>

Field::Field(const Vector2& position, std::size_t width, std::size_t height) 
    : currentTetramino(this->matrix,Color{0,0,0,0}),
      mrd(std::random_device()()),
      randomDist(0,tetraminosCount-1),
      score(0) {

    if(height < 1) height = 1;
    if(width < 1) width = 1;

    this->matrix.resize(height);
     
    for(std::size_t row = 0; row < height; ++row) {
        this->matrix[row].reserve(width);
        for(std::size_t col = 0; col < width; ++col) {
            Vector2 currentPosition {
                static_cast<float>(this->matrix[row][col].getWidth()) * (col+1),
                static_cast<float>(this->matrix[row][col].getHeight()) * (row+1)
            };
            currentPosition.x += position.x;
            currentPosition.y += position.y;
            this->matrix[row].emplace_back(currentPosition);
        }
    }
    
    this->resetTetramino();
}

void Field::update() {
    if(!currentTetramino.update()) {
        this->clearRows();
        this->resetTetramino(); 
    }

}

void Field::render() const { 
    for(const auto& row  : matrix) {
        for(const TetrisCube& cube : row) {
            cube.render();
        }
    }
    currentTetramino.render();
}



void Field::setComplexity(std::size_t complexity) {
    if(complexity < 30 && complexity > 0) {
        currentTetramino.setDelay(1.0/(complexity + 2) - 1);
    }
}

void Field::moveTetraminoRight() {
    currentTetramino.moveRight(0.08);
}

void Field::moveTetraminoLeft() {
    currentTetramino.moveLeft(0.08);
}

void Field::moveTetraminoDown() {
    currentTetramino.moveDown(0.1);
}

void Field::dropTetramino() {
    this->score += 50;
    currentTetramino.drop();
}

void Field::rotateTetramino() {
    currentTetramino.rotate();
}

bool Field::isGameOver() {
    
}


Vector2 Field::getPosition() {
    return this->matrix[0][0].getPosition();
}
std::size_t Field::getWidth() const {
    return this->matrix[0].size() * this->matrix[0][0].getWidth();    
}
std::size_t Field::getHeight() const {
    return this->matrix.size() * this->matrix[0][0].getHeight();
}

std::size_t Field::getScore() {
    return this->score;
}

void Field::moveDown(std::size_t emptyRow) {
    for(std::size_t row = emptyRow-1; row > 0; --row) {
        for(std::size_t col = 0; col < this->matrix[0].size(); ++col) {
            this->matrix[row+1][col] = this->matrix[row][col];
        }
    }
}

void Field::clearRows() {
    int count = 0;
    for(std::size_t row = 0; row < this->matrix.size(); ++row) {
        bool isFullRow = true;
        for(std::size_t col = 0; col < this->matrix[0].size(); ++col) {
            if(this->matrix[row][col].empty()) {
                isFullRow = false;
                break;
            }
        }
        if(isFullRow) {
            count++;
            for(std::size_t col = 0; col < this->matrix[0].size(); ++col) {
                this->matrix[row][col].unfill();
            }
            this->moveDown(row);            
        }
    }
    switch(count) {
        case 1:
            this->score += 100;
            break;
        case 2:
            this->score += 300;
            break;
        case 3:
            this->score += 700;
            break;
        case 4:
            this->score += 1200;
            break;
    }
}

void Field::resetTetramino() {
    switch(randomDist(mrd)) {
        case 0:
            currentTetramino = Hero(this->matrix);
            break;
        case 1:
            currentTetramino = OrangeRicky(this->matrix);
            break;
        case 2:
            currentTetramino = BlueRicky(this->matrix);
            break;
        case 3:
            currentTetramino = RightDog(this->matrix);
            break;
        case 4:
            currentTetramino = LeftDog(this->matrix);
            break;
        case 5:
            currentTetramino = WASD(this->matrix);
            break;
        case 6:
            currentTetramino = Square(this->matrix);
            break;
    }
}
