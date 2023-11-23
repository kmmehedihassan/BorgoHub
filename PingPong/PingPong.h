#pragma once
#include "../Engine.h"
#include <queue>
using namespace borgo;

class PingPong;
class PingPongPlayer
{
    std::set<std::pair<int, int>> position;
    sf::Color color;
    int score;
    PingPong* engine;

public:
    PingPongPlayer(bool isPlayerLeft, PingPong* engine);

    int getScore() const;
    std::set<std::pair<int, int>> getPlayerPosition() const;
    std::map<std::pair<int, int>, sf::Color> getPlayerColor()  const;
    std::pair<int, int> getTopLeftPos() const;
    void moveUp();
    void moveDown();
    void resetPosition(bool isPlayerLeft);
    void incrementScore();

};

class Ball
{
public:
    /// enum definition
    enum Angle {
        _0d, _30d, _45d, _60d, _120d, _135d, _150d, _180d, _210d, _225d, _240d, _300d, _315d, _330d
    };
private:
    Angle angle;
    std::set<std::pair<int, int>> position;
    sf::Color color;
    std::queue<TransformDirection> direction;
    PingPong* engine;


    /*** movement ***/
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void setDirection(Angle a);
public:
    Ball(bool isPlayerLeft, PingPong* engine);

    Angle getAngle();
    void setAngle(Angle a);
    std::set<std::pair<int, int>> getBallPosition() const;
    std::map<std::pair<int, int>, sf::Color> getBallColor()  const;
    std::pair<int, int> getTopLeftPos() const;
    void move();

    /*** Exceptions ***/
    class GameOver {
    public:
        enum GameWinner {
            LeftPlayer, RightPlayer
        };
        GameWinner gameWinner;
        GameOver(GameWinner winner);
    };
    class Collision {
    public:
        enum CollisionType {
            LeftPlayer, RightPlayer, TopWall, BottomWall
        };
        CollisionType collisionType;
        Collision(CollisionType type);
    };
};

class PingPong :
    public Engine
{
    int height;
    int width;
    float delay;
    float timer;
    bool isIdle;
    sf::Color bgcolor;
    PingPongPlayer playerL, playerR;
    Ball ball;

    friend class Ball;
    void handlePlayerCollision(bool isPlayerLeft);
    void handleWallCollision(bool isTopWall);

public:
    PingPong(World& world, ScoreBoard& scoreboard);

    int getWidth();
    int getHeight();
    void start();
    void clear();
    void input();
    void update(float& dt);
    void render();
};



