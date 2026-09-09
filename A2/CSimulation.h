#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLineFollower.h"
#include "CMap.h"
#include "CRender.h"
#include "CWallFollower.h"

#include <string>

// CSimulation owns both A2 robots and their maps. Each update advances both
// robots by the same fixed simulated timestep, while the robots remain
// independent and do not interact.
class CSimulation
{
    public:
        // Loads both maps and places each robot at the starting pose supplied
        // by its corresponding map.
        CSimulation(
            const std::string& aWallMapFilename,
            const std::string& aLineMapFilename );

        // Runs both robots simultaneously until the graphics window closes.
        void Run();

    private:
        // Advances both robots by one fixed simulated timestep.
        void Update( float aDt );

        // Draws both maps, both robot trails and both robots.
        void Render();

        // Reports the run summary.
        void Report() const;

        CRender mRender;

        CMap mWallMap;
        CMap mLineMap;

        CWallFollower mWallFollower;
        CLineFollower mLineFollower;

        int mTotalUpdates{ 0 };

        const float mFixedDt{ 1.0f / 60.0f };

        const float mWallThickness{ 2.0f };
        const float mLineThickness{ 5.0f };

        bool mMapsLoaded{ false };
};

#endif