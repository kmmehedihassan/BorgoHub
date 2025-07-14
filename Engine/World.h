// File: Engine/World.h
#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <set>

namespace borgo {

// Direction enum used by games
enum TransformDirection { Left = 0, Right = 1, Top = 2, Bottom = 3 };

// Stub: minimal world that compiles and is drawable
class World : public sf::Drawable {
    float blockSize;
    unsigned width, height;
    sf::Vector2f position;
    sf::Color bgColor;
public:
    World(float blockSize, unsigned width, unsigned height, sf::Vector2f position)
        : blockSize(blockSize), width(width), height(height), position(position), bgColor(sf::Color::Black) {}

    void clearObject(const std::set<std::pair<int, int>>& ) {}
    void clearObject(const std::map<std::pair<int,int>, sf::Color>& ) {}
    void addObject(const std::map<std::pair<int,int>, sf::Color>& ) {}
    void update() {}

    unsigned getWidth() const { return width; }
    unsigned getHeight() const { return height; }
    float getBlockSize() const { return blockSize; }
    void setBackgroundColor(const sf::Color& color) { bgColor = color; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};

} // namespace borgo