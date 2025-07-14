#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <set>

namespace borgo {

class World : public sf::Drawable {
public:
    World(float blockSize, unsigned width, unsigned height, sf::Vector2f position);

    unsigned getWidth() const;
    unsigned getHeight() const;
    float    getBlockSize() const;

    void setBackgroundColor(sf::Color c);

    void clearObject(const std::set<std::pair<int,int>>& positions);
    void addObject(const std::map<std::pair<int,int>, sf::Color>& objects);
    void update();

    bool checkForObject(const std::pair<int,int>& pos) const;
    std::map<std::pair<int,int>, sf::Color>
        getObjectColors(const std::set<std::pair<int,int>>& positions) const;

private:
    float blockSize;
    unsigned width;
    unsigned height;
    sf::Vector2f origin;
    sf::Color bgColor;

    std::map<std::pair<int,int>, sf::Color> currentObjects;
    std::map<std::pair<int,int>, sf::Color> nextObjects;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

} // namespace borgo
