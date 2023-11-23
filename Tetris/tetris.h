#pragma once
#include "../Engine.h"
#include <iostream>
using namespace borgo;

class Tetris;

class Tetromino {
    uint16_t tetrominoMap[7] = {
        0xF0,  // I
        0x644, // J
        0x622, // L
        0x27,  // T
        0xC60, // Z
        0x360, // S
        0x660  // O
    };
    sf::Color tetrominoColor[7] = {
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::Red,
        sf::Color::Yellow,
        sf::Color::White
    };
    int rotation;
    bool undone; /// allows undo only once
    std::pair<int, int> relBase; /// base point for movement and rotation
    std::pair<int, int> prevBase; /// Previous base point
    std::set<std::pair<int, int>> pos;
    std::set<std::pair<int, int>> prevPos;
    sf::Color color;
    Tetris* engine;

public:
    Tetromino(int index, Tetris* engine);
    Tetromino(int index, int rotation, Tetris* engine);
    std::set<std::pair<int, int>> getPosition() const;
    std::map<std::pair<int, int>, sf::Color> getColors();
    void fallDown();
    void moveLeft();
    void moveRight();
    void rotate();
    bool undoMovement();
};

class TetrisPlayer {
    std::string name;
    int score;
    sf::Time time;

public:
    TetrisPlayer(std::string name);
    std::string getName() const;
    int getScore() const;
    sf::Time getTime() const;
    void setScore(int score);
    void setTime(sf::Time);
    void incrementTime(float& dtAsSeconds);
};

class Tetris :
    public Engine
{
    TetrisPlayer player;
    Tetromino tetromino;
    float timer;
    float delay;
public:
    Tetris(World&, ScoreBoard&);
    Tetris(float, unsigned int, unsigned int, sf::Vector2f&);
    void start();
    void clear();
    void input();
    void update(float&);
    void render();

    bool checkCollision();
    bool checkCollision(const std::pair<int,int>& p);
    void checkCompletedLines();

    int getWidth() const;
    int getHeight() const;
    std::set<std::pair<int, int>> getPlayerPosition();
};

