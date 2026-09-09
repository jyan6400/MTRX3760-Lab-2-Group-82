/*
 * main.cpp
 *
 * This file provides the entry point for the A2 robot simulator. It constructs
 * CSimulation using the supplied wall and line maps and starts both robots
 * running simultaneously.
 */

#include "CSimulation.h"

//-----------------------------------------------------------------------------
int main()
{
    // All simulation behaviour remains encapsulated within CSimulation rather
    // than being implemented directly in main().
    CSimulation Simulation(
        "SimpleWalls.map",
        "SimpleLine.map" );

    Simulation.Run();

    return 0;
}