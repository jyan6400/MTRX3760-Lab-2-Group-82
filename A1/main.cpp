//-----------------------------------------------------------------------------
// main.cpp
//
// Entry point for A1: runs the wall-following simulation on the map file
// named on the command line, or SimpleWalls.map if none is given.
//-----------------------------------------------------------------------------

#include "CSimulation.hpp"

#include <string>

//-----------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    std::string Filename = "SimpleWalls.map";
    if( argc > 1 )
    {
        Filename = argv[1];
    }

    CSimulation Simulation( Filename );
    Simulation.Run();

    return 0;
}