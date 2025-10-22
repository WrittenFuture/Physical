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

    int ParticleCount = 400;

    std::vector<GravParticle> Particles(ParticleCount);

    bool IsRunning = true;
    int Iterations = 0;

    for (int i = 0; i < ParticleCount; i++)
    {
        GravParticle NewParticle;
        NewParticle.SetPos({static_cast<double>(rand() % 1920 - 1920 / 2),
                            static_cast<double>(rand() % 1080 - 1080 / 2),
                            0});

        // Random velocity in range [-7, +7]
        NewParticle.SetVel({static_cast<double>((rand() % 15) - 7),
                            static_cast<double>((rand() % 15) - 7),
                            0});
        NewParticle.SetMass(999999999999999);
        Particles[i] = NewParticle;

        GravSim.AddGravParticle(&Particles[i]);

        std::cout << "Particle " << i << " Position: " << Particles[i].GetPos()[0] << ", " << Particles[i].GetPos()[1] << ", " << Particles[i].GetPos()[2] << std::endl;
    }

    // std::thread StartVisuals(&SimulationManager::StartWindow2D, this);
    StartWindow2D();

    while (IsRunning && Iterations <= 1000)
    {

        GravSim.Update();

        Iterations++;
    }

    return 0;
}

void SimulationManager::StartWindow2D()
{
    Window2D Window(GravSim);
}