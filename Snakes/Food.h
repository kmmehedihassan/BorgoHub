#pragma once
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

class Food
{
    std::pair<int, int> position;
    sf::Color color;
    int points;
public:
    Food(std::pair<int, int> pos);
    std::pair<int, int> getPosition();
    int getPoints();
    sf::Color getColor();
    std::set<std::pair<int, int>> getFoodPosition();
    std::map<std::pair<int, int>, sf::Color> getFoodColor();
};

