// File: Engine/Engine.h
#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "ScoreBoard.h"

namespace borgo {

// Stub: base class for all games, provides a window
class Engine {
protected:
    sf::RenderWindow window;
    World& world;
    ScoreBoard& scoreboard;

public:
    Engine(World& w, ScoreBoard& s)
        : window(sf::VideoMode(
            static_cast<unsigned>(w.getWidth() * w.getBlockSize()),
            static_cast<unsigned>(w.getHeight() * w.getBlockSize())), "BorgoHub"),
          world(w), scoreboard(s) {}

    Engine(float blockSize, unsigned width, unsigned height, sf::Vector2f position)
        : window(sf::VideoMode(
            static_cast<unsigned>(width * blockSize),
            static_cast<unsigned>(height * blockSize)), "BorgoHub"),
          world(*(new World(blockSize, width, height, position))),
          scoreboard(*(new ScoreBoard(blockSize, width, height, position))) {}

    virtual ~Engine() {}

    bool isOpen() const { return window.isOpen(); }
    void close() { window.close(); }
    void clear() { window.clear(); }
    void display() { window.display(); }

    // Allow derived games to access the window directly
    using sf::RenderWindow::draw;
};

} // namespace borgo
