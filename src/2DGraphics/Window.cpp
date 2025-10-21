#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <thread> 
#include "../Simulations/GravityParticles.h"
#include "Window.h"

Window2D::Window2D(GravSimulation& GravSim)
: MainGravSim(GravSim)
{
    // SFML 3: VideoMode now takes a Vector2u instead of (width, height)
    window = sf::RenderWindow(sf::VideoMode({800, 800}), "Gravity Simulation");
    
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition({0, 0});
    circle.setRadius(10);

    circleOrig.setFillColor(sf::Color::Red);
    circleOrig.setPosition({400, -400});
    circleOrig.setRadius(10);

    circle2Orig.setFillColor(sf::Color::Red);
    circle2Orig.setPosition({500, -400});
    circle2Orig.setRadius(10);


    circle2.setFillColor(sf::Color::Cyan);
    circle2.setPosition({300, 200});
    circle2.setRadius(10);

    //GravSim = GravSimulation;

    WaitForClose(); 
};

void Window2D::WaitForClose()
{
    while (window.isOpen())
    {
        // pollEvent now returns std::optional<sf::Event>
        while (auto event = window.pollEvent())
        {
            // Access the event with -> instead of .
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        MainGravSim.Update();

        std::vector<GravParticle*> Particles = MainGravSim.GetParticles();

        CirclePos = sf::Vector2f(Particles[0]->GetPos()[0] + 400, Particles[0]->GetPos()[1] + 400);
        Circle2Pos = sf::Vector2f(Particles[1]->GetPos()[0] + 400, Particles[1]->GetPos()[1] + 400);
        std::cout << Particles[0]->GetPos()[0] << " " << Particles[1]->GetPos()[0] << std::endl;

        circle.setPosition(CirclePos);
        circle2.setPosition(Circle2Pos);

        window.clear();
        window.draw(circleOrig);
        window.draw(circle2Orig);
        window.draw(circle);
        window.draw(circle2);
        window.display();
    }
}
