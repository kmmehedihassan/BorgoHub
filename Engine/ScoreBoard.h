// File: Engine/ScoreBoard.h
#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <utility>

namespace borgo {

// Stub: minimal scoreboard that compiles and is drawable
class ScoreBoard : public sf::Drawable {
    float blockSize;
    unsigned width, height;
    sf::Vector2f position;
    int padding;
    int lineGap;
    sf::Color bgColor;
    sf::Color textColor;
public:
    ScoreBoard(float blockSize, unsigned width, unsigned height, sf::Vector2f position)
        : blockSize(blockSize), width(width), height(height), position(position), padding(0), lineGap(0),
          bgColor(sf::Color::White), textColor(sf::Color::Black) {}

    void clearBoard() {}
    void addScore(const std::pair<std::string, int>& ) {}
    void editScore(const std::string&, int) {}
    void update() {}

    int getPadding() const { return padding; }
    int getLineGap() const { return lineGap; }
    void setPadding(int p) { padding = p; }
    void setBackgroundColor(const sf::Color& color) { bgColor = color; }
    void setTextColor(const sf::Color& color) { textColor = color; }

protected:
    void drawScoreLine(const std::string&, const std::pair<int,int>&, const sf::Color&) {}
    void drawScoreLine(const std::string&, const std::pair<int,int>&) {}

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};

} // namespace borgo