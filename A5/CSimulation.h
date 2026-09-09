/*
 * CSimulation.h
 *
 * This file declares the top-level A5 simulation. It owns two maps and manages
 * twenty wall followers and twenty line followers, each with independently
 * perturbed starting conditions and wheel movement.
 */

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLineFollower.h"
#include "CMap.h"
#include "CRender.h"
#include "CWallFollower.h"

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// CSimulation
//
// CSimulation coordinates the complete A5 experiment. It creates 20 robots of
// each type, applies random starting-pose offsets, enables per-wheel movement
// noise, updates all 40 robots simultaneously and renders their trajectories.
//-----------------------------------------------------------------------------
class CSimulation
{
    public:

        // Loads both maps and constructs twenty noisy robots of each type.
        CSimulation(
            const std::string& aWallMapFilename,
            const std::string& aLineMapFilename );

        // Runs all 40 robots until the graphics window is closed.
        void Run();

    private:

        // Advances every wall and line follower by the same simulated timestep.
        void Update( float aDt );

        // Draws both maps and all forty robots.
        void Render();

        // Prints the final simulation summary.
        void Report() const;

        // Creates a copy of a nominal map pose with independently randomised x,
        // y and heading offsets.
        CPose MakeNoisyPose(
            const CPose& aBasePose ) const;

        // Returns a uniformly distributed random value in
        // [-aMagnitude, +aMagnitude].
        float RandomOffset(
            float aMagnitude ) const;

        CRender mRender;

        CMap mWallMap;
        CMap mLineMap;

        // Dynamic containers hold the required twenty instances of each type.
        std::vector<CWallFollower> mWallFollowers;
        std::vector<CLineFollower> mLineFollowers;

        int mTotalUpdates{ 0 };

        // Number of robots required for each controller type.
        const int mRobotCount{ 20 };

        // Fixed simulated timestep shared by all forty robots.
        const float mFixedDt{ 1.0f / 60.0f };

        const float mWallThickness{ 2.0f };
        const float mLineThickness{ 5.0f };

        // Independent starting x/y perturbation applied to each robot.
        const float mStartPositionNoise{ 3.0f };

        // Approximately three degrees, expressed in radians.
        const float mStartHeadingNoise{ 0.05235988f };

        // Maximum independent fractional wheel-travel variation each update.
        const float mWheelMovementNoiseFraction{ 0.03f };

        bool mMapsLoaded{ false };
};

#endif