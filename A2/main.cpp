// main.cpp
//
// Entry point for A2. Runs the wall-following and line-following robots
// simultaneously using their supplied test maps.

#include "CSimulation.h"

int main()
{
    CSimulation Simulation(
        "SimpleWalls.map",
        "SimpleLine.map" );

    Simulation.Run();

    return 0;
}