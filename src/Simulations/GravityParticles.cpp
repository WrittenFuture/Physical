#include <iostream>
#include <chrono>
#include "GravityParticles.h"

GravSimulation::GravSimulation()
{
    std::cout << "new GravSimulation" << std::endl;
}
void GravSimulation::Update()
{

    for (GravParticle* Body : GravParticles)
    {
        std::vector<double> BodyPos = Body->GetPos();
        double BodyMass = Body->GetMass();

        std::vector<double> NewAcc = {0,0,0};

        for (GravParticle* OtherBody : GravParticles)
        {

            std::vector<double> OtherPos = OtherBody->GetPos();
            double OtherMass = OtherBody->GetMass();

            std::vector<double> Distance = {
                (OtherPos[0] - BodyPos[0]),
                (OtherPos[1] - BodyPos[1]),
                (OtherPos[2] - BodyPos[2])
            };


            for (int Direction = 0; Direction < 3; Direction++)
            {
                if (Distance[Direction] == 0)
                {
                    NewAcc[Direction] += 0;
                    continue;
                }
                else if (Distance[Direction] > 0 )
                {
                    NewAcc[Direction] += 
                    ((GRAVITATIONAL_CONSTANT * OtherMass) / (Distance[Direction] * Distance[Direction]));
                } 
                else if (Distance[Direction] < 0)
                {
                    NewAcc[Direction] += 
                    ((GRAVITATIONAL_CONSTANT * OtherMass) / ((Distance[Direction] * Distance[Direction]) * -1));
                }
            }


        }

        Body->SetAcc(NewAcc);
        Body->Update();
    }

}

void GravSimulation::AddGravParticle(GravParticle* ParticleToAdd)
{
    std::cout << "New Particle added to GravSim" << std::endl;
    GravParticles.push_back(ParticleToAdd);
}

std::vector<GravParticle*> GravSimulation::GetParticles()
{
    return GravParticles;
}


////////////////////////////
///////PARTICLE/////////////
////////////////////////////
GravParticle::GravParticle()
{
    std::cout << "new GravParticle" << std::endl;
    Pos = {0, 0, 0};
    Vel = {0, 0, 0};
    Acc = {0, 0, 0};
    Mass = 0;

    LastUpdate = std::chrono::steady_clock::now();

}

GravParticle::~GravParticle()
{
    std::cout << "ParticleDestroyed" << std::endl;
}

void GravParticle::Update()
{
    std::chrono::time_point<std::chrono::steady_clock> CurrentTime =  std::chrono::steady_clock::now();
    auto Elapsed = std::chrono::duration_cast<std::chrono::microseconds>(CurrentTime - LastUpdate);
    double DeltaTime = static_cast<double>(Elapsed.count());  // microseconds

    for (int Direction = 0; Direction < 3; Direction++)
    {
        Vel[Direction] += Acc[Direction] * DeltaTime / 1'000'000.0;
        Pos[Direction] += Vel[Direction] * DeltaTime / 1'000'000.0;
    }
    LastUpdate = std::chrono::steady_clock::now();
}

void GravParticle::DisplayInfo()
{
    std::cout << Pos[0] << ", " << Pos[1] << ", " << Pos[2] << std::endl;
    std::cout << Acc[0] << ", " << Acc[1] << ", " << Acc[2] << std::endl;
    std::cout << "________________________________" << std::endl;
}

std::vector<double> GravParticle::GetPos() {return Pos;};
std::vector<double> GravParticle::GetVel() {return Vel;};
std::vector<double> GravParticle::GetAcc() {return Acc;};
double GravParticle::GetMass() {return Mass;};

void GravParticle::SetPos(std::vector<double> NewPos)
{
    Pos = NewPos;
}
void GravParticle::SetVel(std::vector<double> NewVel)
{
    Vel = NewVel;
}
void GravParticle::SetAcc(std::vector<double> NewAcc)
{
    Acc = NewAcc;
}
void GravParticle::SetMass(double NewMass)
{
    Mass = NewMass;
}

bool GravParticle::operator==(const GravParticle& other) const
{
    // Define what makes two particles equal
    return Pos == other.Pos && Vel == other.Vel && Acc == other.Acc;
}
