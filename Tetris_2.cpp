#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tetromino.hpp"
#include <deque>
#include <queue>
#include <memory>


const int CellSize = 32;
const int Width = 10, Height = 20;

int board[Width][Height] = {};

int score = 0;


std::deque<std::unique_ptr<Tetromino>> nextQueue;
const int NextQueueSize = 3;



sf::Color getTetrominoColor(char type) {
    switch (type) {
    case 'I': return sf::Color::Cyan;
    case 'O': return sf::Color::Yellow;
    case 'T': return sf::Color(128, 0, 128);
    case 'S': return sf::Color::Green;
    case 'Z': return sf::Color::Red;
    case 'J': return sf::Color::Blue;
    case 'L': return sf::Color(255, 165, 0);
    default: return sf::Color(100, 100, 100);
    }
}

std::unique_ptr<Tetromino> createRandomTetromino(int startX, int startY) {
    int t = rand() % 7;
    switch (t) {
    case 0: return std::make_unique<TetrominoI>(startX, startY);
    case 1: return std::make_unique<TetrominoO>(startX, startY);
    case 2: return std::make_unique<TetrominoT>(startX, startY);
    case 3: return std::make_unique<TetrominoS>(startX, startY);
    case 4: return std::make_unique<TetrominoZ>(startX, startY);
    case 5: return std::make_unique<TetrominoJ>(startX, startY);
    case 6: return std::make_unique<TetrominoL>(startX, startY);
    default: return std::make_unique<TetrominoO>(startX, startY);
    }
}


void fillNextQueue() {
    while (nextQueue.size() < NextQueueSize) {
        nextQueue.push_back(createRandomTetromino(4, 0));
    }
}




bool canMove(const Tetromino& tet, int nextX, int nextY, int nextRot) {
    auto blocks = tet.getOffsets(nextRot);
    for (int i = 0; i < 4; ++i) {
        int x = nextX + blocks[i].x;
        int y = nextY + blocks[i].y;
        if (x < 0 || x >= Width || y < 0 || y >= Height) return false;
        if (board[x][y] != 0) return false;
    }
    return true;
}


bool canMoveDown(const Tetromino& tet) {
    for (const auto& pos : tet.getBlockPositions()) {
        int nx = pos.x;
        int ny = pos.y + 1;
        if (ny >= Height) return false;
        if (nx >= 0 && nx < Width && ny >= 0 && ny < Height && board[nx][ny] != 0)
            return false;
    }
    return true;
}


void lockTetrominoToBoard(const Tetromino& tet) {
    for (const auto& pos : tet.getBlockPositions()) {
        if (pos.x >= 0 && pos.x < Width && pos.y >= 0 && pos.y < Height) {
            board[pos.x][pos.y] = tet.getType();
        }
    }
}

int clearFullLines() {
    int cleared = 0;
    for (int y = Height - 1; y >= 0; --y) {
        bool full = true;
        for (int x = 0; x < Width; ++x)
            if (board[x][y] == 0)
                full = false;
        if (full) {
            for (int yy = y; yy > 0; --yy)
                for (int x = 0; x < Width; ++x)
                    board[x][yy] = board[x][yy - 1];
            for (int x = 0; x < Width; ++x)
                board[x][0] = 0;
            ++cleared;
            ++y;
        }
    }
    return cleared;
}

bool canSpawnTetromino(const Tetromino& tet) {
    for (const auto& pos : tet.getBlockPositions()) {
        if (pos.x < 0 || pos.x >= Width || pos.y < 0 || pos.y >= Height)
            continue;
        if (board[pos.x][pos.y] != 0)
            return false;
    }
    return true;
}



int main() {
    bool koniecGry = false;
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(Width * CellSize, Height * CellSize), "Tetromino losowanie i opadanie");

    fillNextQueue();
    auto tet = std::move(nextQueue.front());
    tet->setPosition(4, 0);
    nextQueue.pop_front();
    fillNextQueue();


    float timer = 0.0f, delay = 0.5f;
    sf::Clock clock;


    sf::Font font;
    font.loadFromFile("C:/Users/filip/source/repos/Tetris_2/x64/Debug/arial.ttf");
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Koniec Gry!\n Wynik: " + std::to_string(score));
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(Width * CellSize / 6, Height * CellSize / 3);


    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;

        if (koniecGry) continue;
        gameOverText.setString("Koniec Gry!\n Wynik: " + std::to_string(score));

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed) {
                int nx = tet->getX();
                int ny = tet->getY();
                int nrot = tet->getRotation();

                if (e.key.code == sf::Keyboard::Left)  nx--;
                if (e.key.code == sf::Keyboard::Right) nx++;
                if (e.key.code == sf::Keyboard::Down)  ny++;
                if (e.key.code == sf::Keyboard::Up)    nrot = (nrot + 1) % 4;

                if (canMove(*tet, nx, ny, nrot)) {
                    tet->setPosition(nx, ny);
                    tet->setRotation(nrot);
                }
            }

        }

        if (timer > delay) {
            int nx = tet->getX();
            int ny = tet->getY() + 1;
            int nrot = tet->getRotation();
            if (canMove(*tet, nx, ny, nrot)) {
                tet->setPosition(nx, ny);
            }
            else {
                lockTetrominoToBoard(*tet);

                int lines = clearFullLines();
                score += lines * 100;

                tet = std::move(nextQueue.front());
                tet->setPosition(4, 0);
                nextQueue.pop_front();
                fillNextQueue();

                if (!canSpawnTetromino(*tet)) {
                    // KONIEC GRY!
                    std::cout << "Koniec Gry! Wynik: " << score << std::endl;
                    koniecGry = true;
                }
            }
            timer = 0;
        }



        window.clear(sf::Color(40, 40, 40));
        for (int x = 0; x < Width; ++x)
            for (int y = 0; y < Height; ++y) {
                sf::RectangleShape rect(sf::Vector2f(CellSize - 2, CellSize - 2));
                rect.setPosition(x * CellSize, y * CellSize);
                rect.setFillColor(sf::Color(50, 50, 50));
                window.draw(rect);
            }

        for (const auto& pos : tet->getBlockPositions()) {
            if (pos.x >= 0 && pos.x < Width && pos.y >= 0 && pos.y < Height) {
                sf::RectangleShape rect(sf::Vector2f(CellSize - 2, CellSize - 2));
                rect.setPosition(pos.x * CellSize, pos.y * CellSize);
                rect.setFillColor(getTetrominoColor(tet->getType()));
                window.draw(rect);
            }
        }

        for (int x = 0; x < Width; ++x)
            for (int y = 0; y < Height; ++y)
                if (board[x][y] != 0) {
                    sf::RectangleShape rect(sf::Vector2f(CellSize - 2, CellSize - 2));
                    rect.setPosition(x * CellSize, y * CellSize);
                    rect.setFillColor(getTetrominoColor(board[x][y]));
                    window.draw(rect);
                }
        if(koniecGry) window.draw(gameOverText);

        window.display();
    }
    return 0;
}
