// src/main.cpp
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "World.h"
#include "ScoreBoard.h"
#include "Snakes/Snakes.h"
#include "PingPong/PingPong.h"
#include "Tetris/tetris.h"

int main() {
    // 1) Create one SFML window for both ImGui and games
    sf::RenderWindow window({800, 600}, "Borgo Game Hub");
    window.setFramerateLimit(60);

    // 2) Initialize ImGui-SFML
    ImGui::SFML::Init(window);

    // 3) Shared engine objects (reset as needed before each game)
    World world(20.f, 12, 20, {0, 0});
    ScoreBoard scoreboard(3.f, 96, 133, {240, 0});

    // 4) Main loop: show menu until user closes window
    sf::Clock deltaClock;
    while (window.isOpen()) {
        // -- Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // -- Start new ImGui frame
        ImGui::SFML::Update(window, deltaClock.restart());

        // -- Build menu UI
        ImGui::Begin("Select a Game");
        if (ImGui::Button("Play Snakes")) {
            // reset world & scoreboard state before each run
            world   = World(20.f, 12, 20, {0, 0});
            scoreboard = ScoreBoard(3.f, 96, 133, {240, 0});
            Snakes(world, scoreboard).start();
        }
        if (ImGui::Button("Play Ping-Pong")) {
            world   = World(20.f, 12, 20, {0, 0});
            scoreboard = ScoreBoard(3.f, 96, 133, {240, 0});
            PingPong(world, scoreboard).start();
        }
        if (ImGui::Button("Play Tetris")) {
            world   = World(20.f, 12, 20, {0, 0});
            scoreboard = ScoreBoard(3.f, 96, 133, {240, 0});
            Tetris(world, scoreboard).start();
        }
        ImGui::End();

        // -- Render ImGui
        window.clear(sf::Color(50, 50, 50));  // dark background
        ImGui::SFML::Render(window);
        window.display();
    }

    // 5) Cleanup
    ImGui::SFML::Shutdown();
    return 0;
}
