#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CMap.h"
#include "CRender.h"
#include "CWallFollower.h"

#include <string>

// CSimulation owns and coordinates the renderer, map and wall-following robot.
// It advances the robot using a fixed simulated timestep and reports run totals.
class CSimulation
{
    public:
        // Loads the map and places the robot at its specified starting pose.
        CSimulation( const std::string& aFilename );

        // Runs the fixed-timestep simulation until the window is closed.
        void Run();

    private:
        // Advances the simulation by one fixed timestep.
        void Update( float aDt );

        // Draws the map and robot.
        void Render();

        // Prints the update and collision totals.
        void Report() const;

        CRender mRender;
        CMap mMap;
        CWallFollower mRobot;

        int mTotalUpdates{ 0 };

        // Simulated timestep is independent of measured real elapsed time.
        const float mFixedDt{ 1.0f / 60.0f };

        // Prevents the simulation running against an invalid map.
        bool mMapLoaded{ false };
};

#endif