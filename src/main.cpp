#include "Simulations/GravityParticles.h"
#include "Simulations/FullSimulation.h"
#include "2DGraphics/Window.h"
#include "main.h"
#include <iostream>
#include <thread>
#include <chrono>

    int main() {
        SimulationManager simManager;
        simManager.main();
        return 0; // return 0 on success
    }
    int SimulationManager::main()
    {
        GravParticle Body;
        GravParticle Body2;
        bool IsRunning = true;
        int Iterations = 0;

        Body2.SetPos({100,50,0});
        Body.SetPos({1,0,0});
        Body2.SetMass(999999999999999);
        Body.SetMass(9999999999999999);

        GravSim.AddGravParticle(&Body);
        GravSim.AddGravParticle(&Body2);

        //std::thread StartVisuals(&SimulationManager::StartWindow2D, this);
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