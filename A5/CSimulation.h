#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLineFollower.h"
#include "CMap.h"
#include "CRender.h"
#include "CWallFollower.h"

#include <string>
#include <vector>

// CSimulation owns and coordinates 20 wall followers and 20 line followers.
// Each robot starts with a small random pose offset and experiences independent
// wheel movement noise during every fixed-timestep update.
class CSimulation
{
    public:
        CSimulation(
            const std::string& aWallMapFilename,
            const std::string& aLineMapFilename );

        void Run();

    private:
        void Update( float aDt );
        void Render();
        void Report() const;

        // Creates a noisy version of a map's nominal starting pose.
        CPose MakeNoisyPose(
            const CPose& aBasePose ) const;

        // Returns a random number in [-aMagnitude, +aMagnitude].
        float RandomOffset(
            float aMagnitude ) const;

        CRender mRender;

        CMap mWallMap;
        CMap mLineMap;

        std::vector<CWallFollower> mWallFollowers;
        std::vector<CLineFollower> mLineFollowers;

        int mTotalUpdates{ 0 };

        const int mRobotCount{ 20 };

        const float mFixedDt{ 1.0f / 60.0f };

        const float mWallThickness{ 2.0f };
        const float mLineThickness{ 5.0f };

        // Maximum random offset applied independently to x and y.
        const float mStartPositionNoise{ 3.0f };

        // Approximately 3 degrees in radians.
        const float mStartHeadingNoise{ 0.05235988f };

        // Each wheel travels within approximately +/-3% of its nominal
        // distance on each update.
        const float mWheelMovementNoiseFraction{ 0.03f };

        bool mMapsLoaded{ false };
};

#endif