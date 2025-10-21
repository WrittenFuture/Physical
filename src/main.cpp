#include "Simulations/GravityParticles.h"
#include "Simulations/FullSimulation.h"
#include "2DGraphics/Window.h"
#include "main.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    SimulationManager simManager;
    simManager.main();
    return 0; // return 0 on success
}
int SimulationManager::main()
{
    GravParticle Body;
    GravParticle Body2;
    GravParticle Body3;

    int ParticleCount = 250;

    std::vector<GravParticle> Particles(ParticleCount);

    bool IsRunning = true;
    int Iterations = 0;

    for (int i = 0; i < ParticleCount; i++)
    {
        GravParticle NewParticle;
        NewParticle.SetPos({static_cast<double>(rand() % 800 - 400), static_cast<double>(rand() % 800 - 400), 0});
        NewParticle.SetVel({static_cast<double>(rand() % 15), static_cast<double>(rand() % 15), 0});
        NewParticle.SetMass(99999999999999999);
        Particles[i] = NewParticle;

        GravSim.AddGravParticle(&Particles[i]);

        std::cout << "Particle " << i << " Position: " << Particles[i].GetPos()[0] << ", " << Particles[i].GetPos()[1] << ", " << Particles[i].GetPos()[2] << std::endl;
    }

    Body2.SetPos({35, 10, 0});
    Body.SetPos({-35, 0, 0});
    Body3.SetPos({0, 35, 0});
    Body3.SetMass(99999999999999999);
    Body2.SetMass(99999999999999999);
    Body.SetMass(99999999999999999);

    Body2.SetVel({0, 10, 0});
    Body3.SetVel({14, -3, 0});

    GravSim.AddGravParticle(&Body);
    GravSim.AddGravParticle(&Body2);
    GravSim.AddGravParticle(&Body3);

    // std::thread StartVisuals(&SimulationManager::StartWindow2D, this);
    StartWindow2D();

    while (IsRunning && Iterations <= 1000)
    {

        GravSim.Update();

        Iterations++;
    }

    Body2.DisplayInfo();

    return 0;
}

void SimulationManager::StartWindow2D()
{
    Window2D Window(GravSim);
}