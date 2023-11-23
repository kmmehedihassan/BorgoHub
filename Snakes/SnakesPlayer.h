#pragma once
#include "Food.h"
#include <queue>
#include "SnakeBody.h"
class SnakesPlayer
{
    std::vector<SnakeBody> body;  /// contains all the body parts
    std::queue<Food> foodsEaten; /// keeps track of the foods eaten in order
    int score;

    bool isDigested(Food& food);
public:
    SnakesPlayer();
    std::pair<int, int> getHeadPosition();
    std::map<std::pair<int, int>, sf::Color> getPlayerColors() const;
    std::set<std::pair<int, int>> getPlayerPosition() const;
    int getScore();
    void setDirection(TransformDirection dir);
    void eatFood(Food& food);
    void moveForward();
    class GameOver {
    };
};

