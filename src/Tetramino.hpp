#pragma once
#include <vector>
#include <array>
#include <raylib.h>


struct TetrisCube {

    TetrisCube(const Vector2& position);
    TetrisCube(const TetrisCube& other);
    TetrisCube& operator=(const TetrisCube& other);
    ~TetrisCube() = default;

    void render() const;
    void fill(const Color& color);
    void unfill();
    bool empty() const;
    
    std::size_t getWidth() const;
    std::size_t getHeight() const;
    const Vector2& getPosition() const;
    
private:

    const Vector2 position;
    
    Color currentColor;

    bool isVoid;
};



class Tetramino {
public:

    using TMatrix = std::vector<std::vector<TetrisCube>>;
    using TIndex = std::pair<std::size_t,std::size_t>;


    Tetramino(TMatrix& matrix, Color color); 
    ~Tetramino() = default;

    Tetramino(Tetramino&& other);
    Tetramino& operator=(Tetramino&& other);

    bool update();
    void render() const;

    void moveRight(double delay);
    void moveLeft(double delay);
    bool moveDown(double delay);
    void drop();
    void rotate();

    void    setDelay(double delay);
    double  getDelay();

    static constexpr std::size_t cubesCount = 4;

protected:

    TMatrix& matrix;
    std::array<TIndex, cubesCount> indexes;  
    Color color;
    double delay;
    double movedDownTime;
    double movedRightTime;
    double movedLeftTime;

    static const std::array<std::array<int,2>,2> rotateMatrix;

};

class Hero : public Tetramino {
public:
    Hero(TMatrix& matrix);
    Hero(const Tetramino& other) = delete;
    Hero& operator=(const Tetramino&) = delete;
    Hero(Tetramino&& other) = delete;
    Hero& operator=(Tetramino&& other) = delete;
};

class OrangeRicky : public Tetramino {
public:
    OrangeRicky(TMatrix& matrix);
    OrangeRicky(const Tetramino& other) = delete;
    OrangeRicky& operator=(const Tetramino&) = delete;
    OrangeRicky(Tetramino&& other) = delete;
    OrangeRicky& operator=(Tetramino&& other) = delete;
};

class BlueRicky : public Tetramino {
public:
    BlueRicky(TMatrix& matrix);
    BlueRicky(const Tetramino& other) = delete;
    BlueRicky& operator=(const Tetramino&) = delete;
    BlueRicky(Tetramino&& other) = delete;
    BlueRicky& operator=(Tetramino&& other) = delete;

};

class RightDog : public Tetramino  {
public:
    RightDog(TMatrix& matrix);
    RightDog(const Tetramino& other) = delete;
    RightDog& operator=(const Tetramino&) = delete;
    RightDog(Tetramino&& other) = delete;
    RightDog& operator=(Tetramino&& other) = delete;
};

class LeftDog : public Tetramino {
public:
    LeftDog(TMatrix& matrix);
    LeftDog(const Tetramino& other) = delete;
    LeftDog& operator=(const Tetramino&) = delete;
    LeftDog(Tetramino&& other) = delete;
    LeftDog& operator=(Tetramino&& other) = delete;
};

class WASD : public Tetramino {
public:
    WASD(TMatrix& matrix);
    WASD(const Tetramino& other) = delete;
    WASD& operator=(const Tetramino&) = delete;
    WASD(Tetramino&& other) = delete;
    WASD& operator=(Tetramino&& other) = delete;
};
class Square : public Tetramino {
public:
    Square(TMatrix& matrix);
    Square(const Tetramino& other) = delete;
    Square& operator=(const Tetramino&) = delete;
    Square(Tetramino&& other) = delete;
    Square& operator=(Tetramino&& other) = delete;
};
