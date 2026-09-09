/*
 * CSimulation.cpp
 *
 * This file implements construction, fixed-timestep execution, rendering,
 * screenshot capture and final reporting for the A1 wall-following simulation.
 */

#include "CSimulation.h"

#include <iostream>

//-----------------------------------------------------------------------------
CSimulation::CSimulation(
    const std::string& aFilename )
    :
        mMap(),
        mRobot( mMap )
{
    mMapLoaded =
        mMap.Load(
            aFilename );

    if( mMapLoaded )
    {
        mRobot.SetPose(
            mMap.GetStartPose() );
    }
    else
    {
        std::cout
            << "CSimulation: failed to load map '"
            << aFilename
            << "'"
            << std::endl;
    }
}

//-----------------------------------------------------------------------------
void CSimulation::Run()
{
    if( mMapLoaded )
    {
        // Rendering occurs in real time, but simulation logic always receives
        // the same fixed timestep rather than measured elapsed time.
        while( !mRender.WindowShouldClose() )
        {
            Update(
                mFixedDt );

            Render();

            // A screenshot is taken only when requested by the user. This
            // allows the completed trajectory to be captured at the desired
            // point without affecting the simulation behaviour.
            if( mRender.ScreenshotRequested() )
            {
                mRender.SaveScreenshot(
                    "A1_WallFollower_Final.png" );

                std::cout
                    << "Screenshot saved as A1_WallFollower_Final.png"
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
    mRobot.Update(
        aDt );

    ++mTotalUpdates;
}

//-----------------------------------------------------------------------------
void CSimulation::Render()
{
    mRender.BeginDrawing();

    // Draw the room before the robot so the robot remains clearly visible.
    mMap.Draw(
        mRender );

    mRobot.Draw(
        mRender );

    mRender.EndDrawing();
}

//-----------------------------------------------------------------------------
void CSimulation::Report() const
{
    std::cout
        << "Total updates: "
        << mTotalUpdates
        << std::endl;

    std::cout
        << "Total collisions: "
        << mRobot.GetCollisionCount()
        << std::endl;
}