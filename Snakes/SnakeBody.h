#pragma once
#include "../World.h"
using namespace borgo;
class SnakeBody
{
    std::pair<int, int> position;
    TransformDirection direction;
    sf::Color color;
public:
    SnakeBody(std::pair<int, int> pos, TransformDirection dir);
    std::pair<int, int> getPosition();
    TransformDirection getDirection();
    sf::Color getColor();
    void setDirection(TransformDirection dir);
    void setPosition(std::pair<int, int> pos);
};

