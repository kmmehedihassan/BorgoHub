#include "World.h"
using namespace borgo;

World::World(float bs, unsigned w, unsigned h, sf::Vector2f orig)
  : blockSize(bs)
  , width(w)
  , height(h)
  , origin(orig)
  , bgColor(sf::Color::Black)
{}

unsigned World::getWidth()    const { return width; }
unsigned World::getHeight()   const { return height; }
float    World::getBlockSize()const { return blockSize; }

void World::setBackgroundColor(sf::Color c) {
    bgColor = c;
}

void World::clearObject(const std::set<std::pair<int,int>>& positions) {
    for (auto& p : positions)
        currentObjects.erase(p);
}

void World::addObject(const std::map<std::pair<int,int>,sf::Color>& objects) {
    for (auto& kv : objects)
        nextObjects[kv.first] = kv.second;
}

void World::update() {
    currentObjects = nextObjects;
    nextObjects.clear();
}

bool World::checkForObject(const std::pair<int,int>& pos) const {
    return currentObjects.count(pos) > 0;
}

std::map<std::pair<int,int>, sf::Color>
World::getObjectColors(const std::set<std::pair<int,int>>& positions) const {
    std::map<std::pair<int,int>, sf::Color> ret;
    for (auto& p : positions) {
        auto it = currentObjects.find(p);
        if (it != currentObjects.end())
            ret[p] = it->second;
    }
    return ret;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // draw background
    sf::RectangleShape background(
        sf::Vector2f(width*blockSize, height*blockSize)
    );
    background.setPosition(origin);
    background.setFillColor(bgColor);
    target.draw(background, states);

    // draw each cell
    for (auto& kv : currentObjects) {
        sf::RectangleShape cell(sf::Vector2f(blockSize, blockSize));
        cell.setPosition(
          origin.x + kv.first.first  * blockSize,
          origin.y + kv.first.second * blockSize
        );
        cell.setFillColor(kv.second);
        target.draw(cell, states);
    }
}
