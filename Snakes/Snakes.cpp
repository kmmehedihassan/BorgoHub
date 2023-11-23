#include "Snakes.h"

Snakes::Snakes(World& w, ScoreBoard& s) : Engine(w, s), food(std::pair<int, int>(15, 6))
{
    bgcolor = sf::Color::Green;
    delay = 0.3f;
    timer = 0.0f;
    world.setBackgroundColor(bgcolor);
}

void Snakes::start()
{
    sf::Clock clock;
    float dt;

    std::pair<std::string, int> score("Score", player.getScore());
    scoreboard.addScore(score);

    while (window.isOpen()) {
        dt = clock.restart().asSeconds();
        input();
        update(dt);
        render();
    }
}

void Snakes::input()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::Up:
                player.setDirection(TransformDirection::Top);
                break;
            case sf::Keyboard::Down:
                player.setDirection(TransformDirection::Bottom);
                break;
            case sf::Keyboard::Left:
                player.setDirection(TransformDirection::Left);
                break;
            case sf::Keyboard::Right:
                player.setDirection(TransformDirection::Right);
                break;
            }
        }
    }
}

void Snakes::update(float& dt)
{
    world.clearObject(player.getPlayerPosition());
    world.clearObject(food.getFoodPosition());
    timer += dt;
    if (timer > delay)
    {
        try {
            player.moveForward();
        }
        catch (SnakesPlayer::GameOver) {
            window.close();
        }
        if (food.getPosition() == player.getHeadPosition()) {
            player.eatFood(food);

            int x, y;
            while (true) {
                x = rand() % 20;
                y = rand() % 12;
                bool isValid = true;
                for (auto p : player.getPlayerPosition()) {
                    if (std::pair<int, int>(x, y) == p) isValid = false;
                }
                if (isValid) break;
            }

            food = Food(std::pair<int, int>(x, y));
        }
        timer = 0.0f;
    }
    world.addObject(food.getFoodColor());
    world.addObject(player.getPlayerColors());
    world.update();
    scoreboard.editScore("Score", player.getScore());
    scoreboard.update();
}

void Snakes::render()
{
    window.clear();
    window.draw(world);
    window.draw(scoreboard);
    window.display();
}
