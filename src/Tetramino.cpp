#include "Textures.hpp"
#include <iostream>
#include "Tetramino.hpp"
#include <raylib.h>


TetrisCube::TetrisCube(const Vector2& position) 
    : position(position), currentColor(BLACK), isVoid(true) {}

TetrisCube::TetrisCube(const TetrisCube& other) 
    : position(other.position), currentColor(other.currentColor), isVoid(other.isVoid) {}

TetrisCube& TetrisCube::operator=(const TetrisCube& other) {
    this->currentColor = other.currentColor;
    this->isVoid = other.isVoid;
    return *this;
}

void TetrisCube::render() const {
    if(this->isVoid)
        DrawTextureEx(
                TetrisTextures::cubeTexture,
                position,
                0.0f,
                1.0f,
                Color{64,64,64,255}
            );
    else {
        DrawTextureEx(TetrisTextures::cubeTexture,
                position,
                0.0f,
                1.0f,
                this->currentColor
            );
    }
}

void TetrisCube::fill(const Color& color) {
    this->currentColor = color;
    isVoid = false;
}

void TetrisCube::unfill() {
    this->currentColor = BLACK;
    isVoid = true;
}

bool TetrisCube::empty() const { 
    return this->isVoid;
}

std::size_t TetrisCube::getWidth() const {
    return TetrisTextures::cubeTexture.width;
}
std::size_t TetrisCube::getHeight() const {
    return TetrisTextures::cubeTexture.height;
}
const Vector2& TetrisCube::getPosition() const {
    return this->position;
}




Tetramino::Tetramino(Tetramino::TMatrix& matrix, Color color)
: matrix(matrix),
  color(color),
  delay(1.0),
  movedDownTime(GetTime()),
  movedRightTime(GetTime()),
  movedLeftTime(GetTime()) {}

Tetramino::Tetramino(Tetramino&& other) 
  : matrix(other.matrix),
    color(other.color),
    movedDownTime(other.movedDownTime),
    movedRightTime(other.movedRightTime),
    movedLeftTime(other.movedLeftTime) {
    std::swap(this->indexes,other.indexes);
}

Tetramino& Tetramino::operator=(Tetramino&& other) {
    std::swap(this->indexes,other.indexes);
    this->color = other.color;
    this->movedDownTime = other.movedDownTime;
    this->movedRightTime = other.movedRightTime;
    this->movedLeftTime = other.movedLeftTime;
    return *this;
}

bool Tetramino::update() {  
    if(this->moveDown(this->delay)) {
        return true;
    }
    else {
        for(auto& [row,col] : indexes) {
            this->matrix[row][col].fill(this->color);
        }
        return false;
    }
}

void Tetramino::render() const {
    for(auto& [row,col] : indexes) {
        DrawTextureEx(
                TetrisTextures::cubeTexture,
                this->matrix[row][col].getPosition(),
                0.0f,
                1.0f,
                this->color
        );
    }
}


void Tetramino::moveRight(double delay) {
    bool canMove = true;
    for(auto& [row,col] : indexes) {
        if(col + 1 >= this->matrix[0].size()) {
            canMove = false;
            break;
        }
        else if(!(this->matrix[row][col+1].empty())) {
            canMove = false;
            break;
        }
    }
    if(canMove) {
        if(GetTime() - this->movedRightTime >= delay) {
            for(auto& [row,col] : indexes) {
                col +=  1UL;
            }
            this->movedRightTime = GetTime();
        }
    }
}
void Tetramino::moveLeft(double delay) {
    bool canMove = true;
    for(auto& [row,col] : indexes) {
        if(static_cast<long>(col) - 1 < 0) {
            canMove = false;
            break;
        }
        else if(!(this->matrix[row][col-1].empty())) {
            canMove = false;
            break;
        }
    }
    if(canMove) {
        if(GetTime() - this->movedLeftTime >= delay) {
            for(auto& [row,col] : indexes) {
                col -=  1UL;
            }
            this->movedLeftTime = GetTime();
        }
    }
}

bool Tetramino::moveDown(double delay) {
    bool canMove = true;
    for(auto& [row,col] : indexes) {
        if(row + 1 >= matrix.size()) {
            canMove = false;
            break;
        }
        else if(!(this->matrix[row+1][col].empty())) {
            canMove = false;
            break;
        }
    }
    if(canMove) {
        if(GetTime() - this->movedDownTime >= delay) {
            for(auto& [row,col] : indexes) {
                row += 1UL;
            }
            this->movedDownTime = GetTime();
        }
    }
    return canMove; 
}

void Tetramino::drop() {
    while(this->moveDown(0.0));
}

const std::array<std::array<int,2>,2> Tetramino::rotateMatrix = {
    std::array<int,2> {0,-1},
    std::array<int,2> {1, 0}
};

void Tetramino::rotate() {
    std::array<std::array<int,cubesCount>,2> indexesMatrix = {
        std::array<int,cubesCount>{},
        std::array<int,cubesCount>{}
    };
    auto resultMatrix = indexesMatrix;

    // Начало координат
    TIndex centerIdx = indexes[cubesCount / 2];
    for(int i = 0; i < cubesCount; ++i) {
        // Вычисляем индексы относительно начала координат
        std::size_t rowIndexDelta = centerIdx.first - indexes[i].first;
        std::size_t colIndexDelta = centerIdx.second - indexes[i].second;
        indexesMatrix[0][i] = rowIndexDelta;
        indexesMatrix[1][i] = colIndexDelta;
    }

    // Перемножить матрицы rotateMatrix и matrix, получить новую матрицу, каждый элемент которой
    // прибавалять к центру, получать нужный индекс и записывать его в indexes 
    for(int i = 0; i < indexesMatrix[0].size(); ++i) {
        resultMatrix[0][i] = rotateMatrix[0][0] * indexesMatrix[0][i];
        resultMatrix[0][i] += rotateMatrix[0][1] * indexesMatrix[1][i];
    }
    for(int i = 0; i < indexesMatrix[0].size(); ++i) {
        resultMatrix[1][i] = rotateMatrix[1][0] * indexesMatrix[0][i];
        resultMatrix[1][i] += rotateMatrix[1][1] * indexesMatrix[1][i];
    }
    
    auto temp = indexes;
    for(int i = 0; i < cubesCount; ++i) { 
        indexes[i].first = centerIdx.first + resultMatrix[0][i];
        indexes[i].second = centerIdx.second + resultMatrix[1][i];
        if(indexes[i].first >= this->matrix.size() || indexes[i].second >= this->matrix[0].size()) {
            this->indexes = temp;
            break;
        }
    }

    for(auto [row,col] : indexes) {
        if(!this->matrix[row][col].empty()) {
            this->indexes = temp;
            break;
        }
    }

}



void Tetramino::setDelay(double delay) {
    this->delay = delay;
}
double Tetramino::getDelay() {
    return this->delay;
}

Hero::Hero(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{0,255,255,255}) {
    this->indexes = {
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{2,this->matrix[0].size()/2},
        TIndex{3,this->matrix[0].size()/2}
    };
}

OrangeRicky::OrangeRicky(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{ORANGE}) {
    this->indexes = {
        TIndex{0,this->matrix[0].size()/2 - 1},
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{2,this->matrix[0].size()/2}
    };
}

BlueRicky::BlueRicky(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{BLUE}) {
    this->indexes = {
        TIndex{0,this->matrix[0].size()/2 + 1},
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{2,this->matrix[0].size()/2}
    };
}

RightDog::RightDog(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{GREEN}) {
    this->indexes = {
        TIndex{0,this->matrix[0].size()/2 + 1},
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2 - 1}
    };
}


LeftDog::LeftDog(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{RED}) {
    this->indexes = {
        TIndex{0,this->matrix[0].size()/2 - 1},
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2 + 1}
    };
}


WASD::WASD(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{PURPLE}) {
    this->indexes = {
        TIndex{1,this->matrix[0].size()/2 + 1},
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2 - 1}
    };
}

Square::Square(Tetramino::TMatrix& matrix) : Tetramino(matrix,Color{YELLOW}) {
    this->indexes = {
        TIndex{0,this->matrix[0].size()/2 + 1},
        TIndex{0,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2},
        TIndex{1,this->matrix[0].size()/2 + 1}
    };
}

