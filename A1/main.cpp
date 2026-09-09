/*
 * main.cpp
 *
 * This file provides the entry point for the A1 wall-following simulator. It
 * selects the requested map file, constructs the top-level CSimulation object
 * and starts the simulation.
 */

#include "CSimulation.h"

#include <string>

//-----------------------------------------------------------------------------
int main(
    int argc,
    char* argv[] )
{
    // Use the supplied A1 room unless another map is named on the command line.
    std::string Filename =
        "SimpleWalls.map";

    if( argc > 1 )
    {
        Filename =
            argv[1];
    }

    // Simulation logic remains encapsulated inside the top-level owner rather
    // than being implemented directly in main().
    CSimulation Simulation(
        Filename );

    Simulation.Run();

    return 0;
}