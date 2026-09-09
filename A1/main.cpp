// main.cpp
//
// Entry point for A1. Runs the wall-following simulation using the map named
// on the command line, or SimpleWalls.map when no filename is provided.

#include "CSimulation.h"

#include <string>

int main( int argc, char* argv[] )
{
    std::string Filename =
        "SimpleWalls.map";

    if( argc > 1 )
    {
        Filename =
            argv[1];
    }

    CSimulation Simulation( Filename );

    Simulation.Run();

    return 0;
}