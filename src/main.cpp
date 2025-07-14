// File: src/main.cpp
#include <SFML/Graphics.hpp>
#include "Snakes/Snakes.h"
#include "PingPong/PingPong.h"
#include "Tetris/tetris.h"

using namespace borgo;

int main() {
    sf::RenderWindow menuWin({800,600}, "BorgoHub Launcher");
    menuWin.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) return -1;

    std::vector<std::string> options = {
        "Play Snakes",
        "Play Ping-Pong",
        "Play Tetris",
        "Quit"
    };
    int selected = 0;

    while (menuWin.isOpen()) {
        sf::Event e;
        while (menuWin.pollEvent(e)) {
            if (e.type == sf::Event::Closed) return 0;
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up)
                    selected = (selected + options.size() - 1) % options.size();
                else if (e.key.code == sf::Keyboard::Down)
                    selected = (selected + 1) % options.size();
                else if (e.key.code == sf::Keyboard::Enter) {
                    if (options[selected] == "Quit")
                        return 0;

                    World world(20.f, 12, 20, {0,0});
                    ScoreBoard scoreboard(3.f, 96, 133, {240,0});

                    if (options[selected] == "Play Snakes") {
                        Snakes(world, scoreboard).start();
                    }
                    else if (options[selected] == "Play Ping-Pong") {
                        PingPong(world, scoreboard).start();
                    }
                    else {
                        Tetris(world, scoreboard).start();
                    }
                }
            }
        }

        menuWin.clear();
        for (int i = 0; i < (int)options.size(); ++i) {
            sf::Text text(options[i], font, 36);
            text.setPosition(200.f, 100.f + i*60.f);
            text.setFillColor(i == selected ? sf::Color::Red : sf::Color::White);
            menuWin.draw(text);
        }
        menuWin.display();
    }

    return 0;
}
