#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "../Simulations/GravityParticles.h"

class Window2D
{
    public:
        Window2D(GravSimulation& GravSim);

    //private:
        sf::RenderWindow window;

        void WaitForClose();
        sf::CircleShape circle;
        sf::CircleShape circle2;

        sf::CircleShape circleOrig;
        sf::CircleShape circle2Orig;

        sf::Vector2f CirclePos;
        sf::Vector2f Circle2Pos;

        GravSimulation& MainGravSim;
};