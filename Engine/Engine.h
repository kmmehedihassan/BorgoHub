#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "ScoreBoard.h"


enum TransformDirection {
    Left,
    Right,
    Top,
    Bottom
};

namespace borgo {

class Engine {
protected:
    sf::RenderWindow window;
    World& world;
    ScoreBoard& scoreboard;

public:
    Engine(World& w, ScoreBoard& s)
      : world(w)
      , scoreboard(s)
      , window(
          sf::VideoMode(
            static_cast<unsigned>(w.getWidth()  * w.getBlockSize()),
            static_cast<unsigned>(w.getHeight() * w.getBlockSize())
          ),
          "BorgoHub"
        )
    {}

    Engine(float blockSize, unsigned width, unsigned height, sf::Vector2f position)
      : world(*(new World(blockSize, width, height, position)))
      , scoreboard(*(new ScoreBoard(blockSize, width, height, position)))
      , window(
          sf::VideoMode(
            static_cast<unsigned>(width  * blockSize),
            static_cast<unsigned>(height * blockSize)
          ),
          "BorgoHub"
        )
    {}

    virtual ~Engine() = default;

    bool isOpen()  const { return window.isOpen(); }
    void close()         { window.close(); }
    void clear()         { window.clear(); }
    void display()       { window.display(); }

    // Draw any SFML drawable
    void draw(const sf::Drawable& d, const sf::RenderStates& s = sf::RenderStates::Default) {
        window.draw(d, s);
    }
};

} // namespace borgo
