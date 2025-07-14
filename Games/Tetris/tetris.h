// File: games/Tetris/tetris.h
#pragma once
#include "../Engine/Engine.h"
#include <iostream>
#include <set>
#include <map>
#include <string>

namespace borgo {

class Tetris;

class Tetromino {
    uint16_t tetrominoMap[7]   = { 0xF0,0x644,0x622,0x27,0xC60,0x360,0x660 };
    sf::Color tetrominoColor[7]= {
        sf::Color::Cyan, sf::Color::Blue,  sf::Color::Green,
        sf::Color::Magenta, sf::Color::Red, sf::Color::Yellow,
        sf::Color::White
    };
    int rotation;
    bool undone;
    std::pair<int,int> relBase, prevBase;
    std::set<std::pair<int,int>> pos, prevPos;
    sf::Color color;
    Tetris* engine;

public:
    Tetromino(int index, Tetris* engine);
    Tetromino(int index, int rotation, Tetris* engine);

    std::set<std::pair<int,int>> getPosition() const;
    std::map<std::pair<int,int>, sf::Color> getColors() const;

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
    TetrisPlayer(const std::string& name);
    std::string getName() const;
    int getScore() const;
    sf::Time getTime() const;
    void setScore(int score);
    void setTime(sf::Time t);
    void incrementTime(float dtAsSeconds);
};

class Tetris : public Engine {
    TetrisPlayer player;
    Tetromino    tetromino;
    float        timer;
    float        delay;

public:
    Tetris(World& world, ScoreBoard& scoreboard);
    Tetris(float bs, unsigned w, unsigned h, sf::Vector2f pos);

    void start();
    void clear();
    void input();
    void update(float dt);
    void render();

    bool checkCollision() const;
    bool checkCollision(const std::pair<int,int>& p) const;
    void checkCompletedLines();

    int getWidth()  const;
    int getHeight() const;
    std::set<std::pair<int,int>> getPlayerPosition() const;
};

} // namespace borgo
