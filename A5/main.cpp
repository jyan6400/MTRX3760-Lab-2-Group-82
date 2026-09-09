// main.cpp
//
// Entry point for the A5 noise bonus. Runs 20 wall-following robots and
// 20 line-following robots simultaneously with random starting pose and
// wheel-movement perturbations.

#include "CSimulation.h"

int main()
{
    CSimulation Simulation(
        "SimpleWalls.map",
        "SimpleLine.map" );

    Simulation.Run();

    return 0;
}