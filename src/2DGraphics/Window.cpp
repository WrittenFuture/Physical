#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <thread>
#include "../Simulations/GravityParticles.h"
#include "Window.h"

Window2D::Window2D(GravSimulation &GravSim)
    : MainGravSim(GravSim)
{
    // SFML 3: VideoMode now takes a Vector2u instead of (width, height)
    window = sf::RenderWindow(sf::VideoMode({800, 800}), "Gravity Simulation");

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
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        MainGravSim.Update(); // ideally with fixed timestep

        auto Particles = MainGravSim.GetParticles();
        for (size_t i = 0; i < Particles.size(); i++)
        {
            Circles[i].setRadius(5);
            Circles[i].setFillColor(sf::Color::Cyan);
            CirclePositions[i] = sf::Vector2f(Particles[i]->GetPos()[0] + 400, Particles[i]->GetPos()[1] + 400);
            Circles[i].setPosition(CirclePositions[i]);
        }

        window.clear();
        for (auto &circle : Circles)
            window.draw(circle);
        window.display();
    }
}
