#include "ScoreBoard.h"
#include <iostream>
using namespace borgo;

class Menu : public ScoreBoard{
    std::string title;
    sf::Color titleColor;
    sf::Color selectedColor;
    std::vector<std::string> options;
    int selected;
    bool running;
public:
    Menu(float blockSize, uint32_t width, uint32_t height, sf::Vector2f position)
    : ScoreBoard(blockSize, width, height, position), running(true){
        title = "Menu";
        titleColor = sf::Color::Green;
        selectedColor = sf::Color::Blue;
        selected = 0;
    }

    bool isRunning(){
        return running;
    }

    void setOptions(std::vector<std::string> options){
        this->options = options;
    }
    void updateColorMap(){
        std::pair<int, int> cursor(getPadding(), getPadding());
        drawScoreLine(title, cursor, titleColor);
        cursor.first = getPadding();
        cursor.second += 8 + getLineGap();

        for (int i=0; i<options.size(); i++) {
            if(i == selected) drawScoreLine(options[i], cursor, selectedColor);
            else drawScoreLine(options[i], cursor);
            cursor.first = getPadding();
            cursor.second += 8 + getLineGap();
        }
    }
    void moveUp(){
        selected -=1;
        if(selected < 0) selected+=options.size();
    }
    void moveDown(){
        selected = (selected + 1)%options.size();
    }
    void handleOptions(){
        switch(selected){
        case 0:
            ///start game
            break;
        case 1:
            /// leaderboard
            break;
        case 2:
            /// quit
            running = false;
            break;
        }
    }
};
