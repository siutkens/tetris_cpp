#pragma once
#include <array>
#include <SFML/Graphics.hpp>

class Tetromino {
protected:
    int x, y;
    int rotation;
public:
    Tetromino(int startX, int startY) : x(startX), y(startY), rotation(0) {}
    virtual ~Tetromino() {}

    std::array<sf::Vector2i, 4> getBlockPositions() const {
        auto offsets = getOffsets();
        std::array<sf::Vector2i, 4> positions;
        for (int i = 0; i < 4; ++i)
            positions[i] = sf::Vector2i(x, y) + offsets[i];
        return positions;
    }

    virtual std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const = 0;
    virtual char getType() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    int getRotation() const { return rotation; }

    void setPosition(int nx, int ny) { x = nx; y = ny; }
    void setRotation(int r) { rotation = r % 4; }
    void rotateCW() { rotation = (rotation + 1) % 4; }
    void rotateCCW() { rotation = (rotation + 3) % 4; }
};

class TetrominoI : public Tetromino {
    std::array<std::array<sf::Vector2i, 4>, 4> rotations;
public:
    TetrominoI(int startX, int startY) : Tetromino(startX, startY) {
        rotations = { {
            {sf::Vector2i(0,1), sf::Vector2i(1,1), sf::Vector2i(2,1), sf::Vector2i(3,1)},
            {sf::Vector2i(2,0), sf::Vector2i(2,1), sf::Vector2i(2,2), sf::Vector2i(2,3)},
            {sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(3,2)},
            {sf::Vector2i(1,0), sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(1,3)}
        } };
    }
    std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const override {
        if (rot == -1) rot = rotation;
        return rotations[rot % 4];
    }
    char getType() const override { return 'I'; }
};

class TetrominoO : public Tetromino {
public:
    TetrominoO(int startX, int startY) : Tetromino(startX, startY) {}
    std::array<sf::Vector2i, 4> getOffsets(int /*rot*/ = -1) const override {
        return { sf::Vector2i(1,1), sf::Vector2i(2,1), sf::Vector2i(1,2), sf::Vector2i(2,2) };
    }
    char getType() const override { return 'O'; }
};

class TetrominoT : public Tetromino {
    std::array<std::array<sf::Vector2i, 4>, 4> rotations;
public:
    TetrominoT(int startX, int startY) : Tetromino(startX, startY) {
        rotations = { {
            {sf::Vector2i(1,1), sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2)},
            {sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(1,3)},
            {sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(1,3)},
            {sf::Vector2i(1,1), sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(1,3)}
        } };
    }
    std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const override {
        if (rot == -1) rot = rotation;
        return rotations[rot % 4];
    }
    char getType() const override { return 'T'; }
};

class TetrominoS : public Tetromino {
    std::array<std::array<sf::Vector2i, 4>, 4> rotations;
public:
    TetrominoS(int startX, int startY) : Tetromino(startX, startY) {
        rotations = { {
            {sf::Vector2i(1,1), sf::Vector2i(2,1), sf::Vector2i(0,2), sf::Vector2i(1,2)},
            {sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(2,3)},
            {sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(0,3), sf::Vector2i(1,3)},
            {sf::Vector2i(0,1), sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(1,3)}
        } };
    }
    std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const override {
        if (rot == -1) rot = rotation;
        return rotations[rot % 4];
    }
    char getType() const override { return 'S'; }
};

class TetrominoZ : public Tetromino {
    std::array<std::array<sf::Vector2i, 4>, 4> rotations;
public:
    TetrominoZ(int startX, int startY) : Tetromino(startX, startY) {
        rotations = { {
            {sf::Vector2i(0,1), sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(2,2)},
            {sf::Vector2i(2,1), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(1,3)},
            {sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(1,3), sf::Vector2i(2,3)},
            {sf::Vector2i(1,1), sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(0,3)}
        } };
    }
    std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const override {
        if (rot == -1) rot = rotation;
        return rotations[rot % 4];
    }
    char getType() const override { return 'Z'; }
};

class TetrominoJ : public Tetromino {
    std::array<std::array<sf::Vector2i, 4>, 4> rotations;
public:
    TetrominoJ(int startX, int startY) : Tetromino(startX, startY) {
        rotations = { {
            {sf::Vector2i(0,1), sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2)},
            {sf::Vector2i(1,1), sf::Vector2i(2,1), sf::Vector2i(1,2), sf::Vector2i(1,3)},
            {sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(2,3)},
            {sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(0,3), sf::Vector2i(1,3)}
        } };
    }
    std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const override {
        if (rot == -1) rot = rotation;
        return rotations[rot % 4];
    }
    char getType() const override { return 'J'; }
};

class TetrominoL : public Tetromino {
    std::array<std::array<sf::Vector2i, 4>, 4> rotations;
public:
    TetrominoL(int startX, int startY) : Tetromino(startX, startY) {
        rotations = { {
            {sf::Vector2i(2,1), sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2)},
            {sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(1,3), sf::Vector2i(2,3)},
            {sf::Vector2i(0,2), sf::Vector2i(1,2), sf::Vector2i(2,2), sf::Vector2i(0,3)},
            {sf::Vector2i(0,1), sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(1,3)}
        } };
    }
    std::array<sf::Vector2i, 4> getOffsets(int rot = -1) const override {
        if (rot == -1) rot = rotation;
        return rotations[rot % 4];
    }
    char getType() const override { return 'L'; }
};
