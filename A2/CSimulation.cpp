#include "CSimulation.h"

#include <iostream>

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

    if( WallMapLoaded )
    {
        mWallFollower.SetPose(
            mWallMap.GetStartPose() );
    }

    if( LineMapLoaded )
    {
        mLineFollower.SetPose(
            mLineMap.GetStartPose() );
    }

    if( !mMapsLoaded )
    {
        std::cout
            << "CSimulation: failed to load one or more maps"
            << std::endl;
    }
}

void CSimulation::Run()
{
    if( mMapsLoaded )
    {
        while( !mRender.WindowShouldClose() )
        {
            Update(
                mFixedDt );

            Render();
        }
    }

    mRender.CloseWindow();

    Report();
}

void CSimulation::Update(
    float aDt )
{
    mWallFollower.Update(
        aDt );

    mLineFollower.Update(
        aDt );

    ++mTotalUpdates;
}

void CSimulation::Render()
{
    mRender.BeginDrawing();

    // Draw the room walls.
    mWallMap.Draw(
        mRender,
        CRender::COLOUR_WHITE,
        mWallThickness );

    // Draw the 5-unit-wide floor line.
    mLineMap.Draw(
        mRender,
        CRender::COLOUR_GREY,
        mLineThickness );

    // Draw both robots and their permanent trails.
    mWallFollower.Draw(
        mRender );

    mLineFollower.Draw(
        mRender );

    mRender.EndDrawing();
}

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