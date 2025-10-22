#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../Simulations/GravityParticles.h"
#include "Window.h"

Window2D::Window2D(GravSimulation &GravSim)
    : MainGravSim(GravSim)
{
    // SFML 3: VideoMode now takes a Vector2u instead of (width, height)
    // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window = sf::RenderWindow(sf::VideoMode({WindowWidth, WindowHeight}), "Gravity Simulation");

    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition({0, 0});
    circle.setRadius(10);

    circle2.setFillColor(sf::Color::Cyan);
    circle2.setPosition({300, 200});
    circle2.setRadius(10);

    circle3.setFillColor(sf::Color::Cyan);
    circle3.setPosition({300, 200});
    circle3.setRadius(10);

    // GravSim = GravSimulation;

    WaitForClose();
};

void Window2D::WaitForClose()
{
    Circles.resize(MainGravSim.GetParticles().size());
    CirclePositions.resize(Circles.size());

    while (window.isOpen())
    {
        while (auto eventOpt = window.pollEvent())
        {
            const sf::Event &event = *eventOpt;

            if (event.is<sf::Event::Closed>())
                window.close();
        }
        MainGravSim.Update(); // ideally with fixed timestep

        auto Particles = MainGravSim.GetParticles();
        for (size_t i = 0; i < Particles.size(); i++)
        {
            Circles[i].setRadius(5);
            Circles[i].setFillColor(sf::Color::Cyan);
            CirclePositions[i] = sf::Vector2f(Particles[i]->GetPos()[0] + ((WindowWidth) / 2), Particles[i]->GetPos()[1] + ((WindowHeight) / 2));
            float clampedX = std::clamp(CirclePositions[i].x, 0.f, static_cast<float>(WindowWidth));
            float clampedY = std::clamp(CirclePositions[i].y, 0.f, static_cast<float>(WindowHeight));
            Circles[i].setPosition({clampedX, clampedY});
        }

        window.clear();
        for (auto &circle : Circles)
            window.draw(circle);
        window.display();
    }
}
