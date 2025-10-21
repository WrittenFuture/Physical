#pragma once
#include <vector>
#include <chrono>
class GravParticle
{
private:
    std::vector<double> Pos;
    std::vector<double> Vel;
    std::vector<double> Acc;
    double Mass;

    std::chrono::time_point<std::chrono::steady_clock> LastUpdate;

public:
    GravParticle();
    ~GravParticle();

    std::vector<double> GetPos();
    std::vector<double> GetVel();
    std::vector<double> GetAcc();
    double GetMass();

    void SetPos(std::vector<double> NewPos);
    void SetVel(std::vector<double> NewVel);
    void SetAcc(std::vector<double> NewAcc);
    void SetMass(double NewMass);

    void Update();

    void DisplayInfo();

    bool operator==(const GravParticle &other) const;
};

class GravSimulation
{

public:
    GravSimulation();
    void Update();
    void AddGravParticle(GravParticle *ParticleToAdd);
    std::vector<GravParticle *> GetParticles();

private:
    std::vector<GravParticle *> GravParticles;
    std::chrono::time_point<std::chrono::steady_clock> LastSimUpdate;
    double GRAVITATIONAL_CONSTANT = 6.67430e-11;
};