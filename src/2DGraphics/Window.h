#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "../Simulations/GravityParticles.h"

class Window2D
{
public:
    Window2D(GravSimulation &GravSim);

    // private:
    sf::RenderWindow window;

    void WaitForClose();
    sf::CircleShape circle;
    sf::CircleShape circle2;
    sf::CircleShape circle3;

    std::vector<sf::CircleShape> Circles;

    sf::Vector2f CirclePos;
    sf::Vector2f Circle2Pos;
    sf::Vector2f Circle3Pos;

    std::vector<sf::Vector2f> CirclePositions;

    GravSimulation &MainGravSim;

    unsigned int WindowWidth = 1920;
    unsigned int WindowHeight = 1080;
};