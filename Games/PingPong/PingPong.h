#pragma once

#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <climits>

namespace borgo {

class PingPong;
enum TransformDirection { Left, Right, Top, Bottom };

class PingPongPlayer {
    std::set<std::pair<int,int>> position;
    sf::Color color;
    int score;
    PingPong* engine;

public:
    PingPongPlayer(bool isPlayerLeft, PingPong* engine);

    int getScore() const;
    std::set<std::pair<int,int>> getPlayerPosition() const;
    std::map<std::pair<int,int>, sf::Color> getPlayerColor() const;
    std::pair<int,int> getTopLeftPos() const;
    void moveUp();
    void moveDown();
    void resetPosition(bool isPlayerLeft);
    void incrementScore();
};

class Ball {
public:
    enum Angle {
        _0d, _30d, _45d, _60d,
        _120d, _135d, _150d, _180d,
        _210d, _225d, _240d,
        _300d, _315d, _330d
    };

    struct GameOver {
        enum GameWinner { LeftPlayer, RightPlayer };
        GameWinner gameWinner;
        GameOver(GameWinner winner) : gameWinner(winner) {}
    };

    struct Collision {
        enum CollisionType { LeftPlayer, RightPlayer, TopWall, BottomWall };
        CollisionType collisionType;
        Collision(CollisionType type) : collisionType(type) {}
    };

private:
    Angle angle;
    std::set<std::pair<int,int>> position;
    sf::Color color;
    std::queue<TransformDirection> direction;
    PingPong* engine;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void setDirection(Angle a);

public:
    Ball(bool isPlayerLeft, PingPong* engine);

    Angle getAngle() const;
    void setAngle(Angle a);
    std::set<std::pair<int,int>> getBallPosition() const;
    std::map<std::pair<int,int>, sf::Color> getBallColor() const;
    std::pair<int,int> getTopLeftPos() const;
    void move();
};

class PingPong : public Engine {
    int height, width;
    float delay, timer;
    bool isIdle;
    sf::Color bgcolor;

public:
    PingPongPlayer playerL;
    PingPongPlayer playerR;
    Ball ball;

    PingPong(World& world, ScoreBoard& scoreboard);

    int getWidth() const;
    int getHeight() const;
    void start();
    void clear();
    void input();
    void update(float& dt);
    void render();

    void handlePlayerCollision(bool isPlayerLeft);
    void handleWallCollision(bool isTopWall);
};

} // namespace borgo
