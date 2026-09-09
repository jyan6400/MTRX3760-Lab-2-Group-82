/*
 * main.cpp
 *
 * This file provides the entry point for the A5 noise simulation. It
 * constructs the top-level CSimulation using the supplied wall and line maps
 * and starts the forty-robot experiment.
 */

#include "CSimulation.h"

//-----------------------------------------------------------------------------
int main()
{
    // All A5 population creation, noise generation and simulation behaviour
    // remain encapsulated within CSimulation.
    CSimulation Simulation(
        "SimpleWalls.map",
        "SimpleLine.map" );

    Simulation.Run();

    return 0;
}