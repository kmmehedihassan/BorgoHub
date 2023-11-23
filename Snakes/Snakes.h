#pragma once
#include "../Engine.h"
#include "SnakeBody.h"
#include "SnakesPlayer.h"
#include "Food.h"
using namespace borgo;

class Snakes :
    public Engine
{
    float delay;
    float timer;
    sf::Color bgcolor;

    SnakesPlayer player;
    Food food;

public:
    Snakes(World& w, ScoreBoard& s);
    void start();
    void input();
    void update(float& dt);
    void render();
};

