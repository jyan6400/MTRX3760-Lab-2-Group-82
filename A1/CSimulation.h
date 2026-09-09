/*
 * CSimulation.h
 *
 * This file declares the top-level A1 simulation object. It owns the renderer,
 * room map and wall-following robot and coordinates the fixed-timestep
 * simulation.
 */

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CMap.h"
#include "CRender.h"
#include "CWallFollower.h"

#include <string>

//-----------------------------------------------------------------------------
// CSimulation
//
// CSimulation is the top-level owner of the A1 system. It constructs and
// coordinates the map, wall follower and renderer, advances the robot using a
// fixed simulated timestep, renders each frame and prints the final summary.
//-----------------------------------------------------------------------------
class CSimulation
{
    public:

        // Loads aFilename and places the wall follower at the starting pose
        // specified by that map.
        CSimulation( const std::string& aFilename );

        // Runs the simulation until the graphics window is closed.
        void Run();

    private:

        // Advances the wall follower by one simulated timestep and records one
        // completed simulation update.
        void Update( float aDt );

        // Draws the environment and robot for the current frame.
        void Render();

        // Prints the required update and collision totals at the end of a run.
        void Report() const;

        // Graphics interface owned by the simulation.
        CRender mRender;

        // Room geometry owned by the simulation.
        CMap mMap;

        // Wall follower owned by the simulation. It knows mMap by reference.
        CWallFollower mRobot;

        // Number of fixed simulated updates completed.
        int mTotalUpdates{ 0 };

        // Fixed amount of simulated time advanced each update. It is not based
        // on measured real elapsed time.
        const float mFixedDt{ 1.0f / 60.0f };

        // Prevents the update loop from running if map loading failed.
        bool mMapLoaded{ false };
};

#endif