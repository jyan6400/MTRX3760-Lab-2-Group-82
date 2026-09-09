/*
 * CSimulation.cpp
 *
 * This file implements construction, simultaneous fixed-timestep execution,
 * rendering, screenshot capture and final reporting for the A2 simulation.
 */

#include "CSimulation.h"

#include <iostream>

//-----------------------------------------------------------------------------
CSimulation::CSimulation(
    const std::string& aWallMapFilename,
    const std::string& aLineMapFilename )
    :
        mWallMap(),
        mLineMap(),
        mWallFollower( mWallMap ),
        mLineFollower( mLineMap )
{
    bool WallMapLoaded =
        mWallMap.Load(
            aWallMapFilename );

    bool LineMapLoaded =
        mLineMap.Load(
            aLineMapFilename );

    mMapsLoaded =
        WallMapLoaded
        && LineMapLoaded;

    if( mMapsLoaded )
    {
        mWallFollower.SetPose(
            mWallMap.GetStartPose() );

        mLineFollower.SetPose(
            mLineMap.GetStartPose() );
    }
    else
    {
        std::cout
            << "CSimulation: failed to load one or more maps"
            << std::endl;
    }
}

//-----------------------------------------------------------------------------
void CSimulation::Run()
{
    if( mMapsLoaded )
    {
        // Both robots receive exactly the same fixed amount of simulated time
        // during every logical update.
        while( !mRender.WindowShouldClose() )
        {
            Update(
                mFixedDt );

            Render();

            // Press S once both permanent trails show complete circuits.
            if( mRender.ScreenshotRequested() )
            {
                mRender.SaveScreenshot(
                    "A2_RobotSimulator_Final.png" );

                std::cout
                    << "Screenshot saved as A2_RobotSimulator_Final.png"
                    << std::endl;
            }
        }
    }

    mRender.CloseWindow();

    Report();
}

//-----------------------------------------------------------------------------
void CSimulation::Update( float aDt )
{
    // The two robots are updated independently and do not interact.
    mWallFollower.Update(
        aDt );

    mLineFollower.Update(
        aDt );

    ++mTotalUpdates;
}

//-----------------------------------------------------------------------------
void CSimulation::Render()
{
    mRender.BeginDrawing();

    // The wall is drawn as a narrow white boundary and the line as an exactly
    // five-unit-wide grey floor marking.
    mWallMap.Draw(
        mRender,
        CRender::COLOUR_WHITE,
        mWallThickness );

    mLineMap.Draw(
        mRender,
        CRender::COLOUR_GREY,
        mLineThickness );

    mWallFollower.Draw(
        mRender );

    mLineFollower.Draw(
        mRender );

    mRender.EndDrawing();
}

//-----------------------------------------------------------------------------
void CSimulation::Report() const
{
    std::cout
        << "Simulation updates: "
        << mTotalUpdates
        << std::endl;

    std::cout
        << "Wall follower collisions: "
        << mWallFollower.GetCollisionCount()
        << std::endl;

    std::cout
        << "Wall follower updates: "
        << mTotalUpdates
        << std::endl;

    std::cout
        << "Line follower updates: "
        << mTotalUpdates
        << std::endl;
}