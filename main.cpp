#include <iostream>
#include "Snakes/Snakes.h"
#include "PingPong/PingPong.h"
#include "Tetris/tetris.h"
using namespace borgo;

int main() {

//    borgo::World world(12.f, 56, 32, sf::Vector2f(0,0));
//    borgo::ScoreBoard scoreboard(3.f, 96, 80, sf::Vector2f(672, 0));
//    PingPong pingpong(world, scoreboard);
//    pingpong.start();

//    World world(20.f, 20, 12, sf::Vector2f(0, 0));
//    ScoreBoard scoreboard(3.f, 96, 80, sf::Vector2f(400, 0));
//    Snakes snakes(world, scoreboard);
//    snakes.start();

//    World world(20.f, 40, 20, sf::Vector2f(0, 0));
//    ScoreBoard scoreboard(3.f, 70, 130, sf::Vector2f(810, 0));
//    Trial trial(world, scoreboard);
//    trial.start();

    sf::Vector2f position(10.f, 10.f);
    World world(20.f, 12, 20, sf::Vector2f(0,0));
    ScoreBoard scoreboard(3.f, 96, 133, sf::Vector2f(240, 0));
	Tetris tetris(world,scoreboard);
	tetris.start();


	// For Debugging purposes on Scoreboard
//	ScoreBoard sb(3.f, 400, 80, sf::Vector2f(0, 0));
//	sb.setPadding(1);
//	std::pair<std::string, int> sc1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);
//	std::pair<std::string, int> sc2("abcdefghijklmnopqrstuvwxyz", 1);
//
//	sb.addScore(sc1);
//	sb.addScore(sc2);
//
//	sf::Vector2f resolution;
//	resolution.x = sf::VideoMode::getDesktopMode().width;
//	resolution.y = sf::VideoMode::getDesktopMode().height;
//
//	sf::RenderWindow window(sf::VideoMode(800, 50),
//		"Simple Game Engine",
//		sf::Style::Titlebar | sf::Style::Close);
//
//	window.setFramerateLimit(30);
//	while (window.isOpen()) {
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            window.close();
//        }
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//		{
//			window.close();
//		}
//		try {
//			sb.update();
//		}
//		catch (ScoreBoard::MapWidthExceeded) {
//			std::cout << "ColorMap out of range" << std::endl;
//			window.close();
//		}
//		window.clear();
//		window.draw(sb);
//		window.display();
//	}
//
//    Menu menu(3.f, 400, 400, sf::Vector2f(0, 0));
//    menu.setLineGap(20);
//    std::vector<std::string> ops({"Start Game", "Leader board", "Quit"});
//    for(auto s : ops) std::cout<<s<<std::endl;
//    menu.setOptions(ops);
//    sf::RenderWindow window(sf::VideoMode(400, 400),
//		"Sample Menu",
//		sf::Style::Titlebar | sf::Style::Close);
//
//	window.setFramerateLimit(60);
//	while (window.isOpen()) {
//        if (!menu.isRunning())
//        {
//            window.close();
//        }
////        if (sf::Event::Closed) {
////            window.close();
////        }
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//		{
//			window.close();
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//		{
//            menu.moveUp();
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//		{
//			menu.moveDown();
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
//		{
//			menu.handleOptions();
//		}
//		try {
//			menu.update();
//		}
//		catch (ScoreBoard::MapWidthExceeded) {
//			std::cout<<"Map width exceeded"<<std::endl;
//		}
//		window.clear();
//		window.draw(menu);
//		window.display();
//	}

    return 0;

}
