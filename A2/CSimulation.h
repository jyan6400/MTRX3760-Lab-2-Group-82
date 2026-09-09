/*
 * CSimulation.h
 *
 * This file declares the top-level A2 simulation object. It owns the renderer,
 * wall map, line map, wall follower and line follower and coordinates their
 * simultaneous fixed-timestep execution.
 */

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLineFollower.h"
#include "CMap.h"
#include "CRender.h"
#include "CWallFollower.h"

#include <string>

//-----------------------------------------------------------------------------
// CSimulation
//
// CSimulation is the top-level owner of the A2 system. It loads both maps,
// positions both robots, advances them once per fixed simulation update,
// renders the complete scene and reports the final run statistics.
//-----------------------------------------------------------------------------
class CSimulation
{
    public:

        // Loads the supplied wall and line maps and places each robot at the
        // starting pose defined by its corresponding map.
        CSimulation(
            const std::string& aWallMapFilename,
            const std::string& aLineMapFilename );

        // Runs both robots simultaneously until the window is closed.
        void Run();

    private:

        // Advances both robot controllers by the same simulated timestep.
        void Update( float aDt );

        // Draws both maps and both robots for the current frame.
        void Render();

        // Prints the final simulation and wall-collision statistics.
        void Report() const;

        // Graphics interface owned by the simulation.
        CRender mRender;

        // Separate geometry for the room boundary and floor line.
        CMap mWallMap;
        CMap mLineMap;

        // One wall follower and one line follower run simultaneously.
        CWallFollower mWallFollower;
        CLineFollower mLineFollower;

        // Number of fixed updates completed by the simulation.
        int mTotalUpdates{ 0 };

        // Fixed simulated timestep, independent of measured elapsed time.
        const float mFixedDt{ 1.0f / 60.0f };

        // Required visual widths of wall and floor-line geometry.
        const float mWallThickness{ 2.0f };
        const float mLineThickness{ 5.0f };

        // Prevents simulation execution unless both maps loaded successfully.
        bool mMapsLoaded{ false };
};

#endif