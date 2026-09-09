/*
 * CSimulation.cpp
 *
 * This file implements the A5 noise experiment. It constructs twenty robots
 * of each type with random starting poses, enables independent wheel-travel
 * noise, updates all robots together, renders their trajectories and supports
 * on-demand screenshot capture.
 */

#include "CSimulation.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

//-----------------------------------------------------------------------------
CSimulation::CSimulation(
    const std::string& aWallMapFilename,
    const std::string& aLineMapFilename )
    :
        mWallMap(),
        mLineMap()
{
    // Seed once so each simulation run produces a different set of starting
    // conditions and wheel perturbations.
    std::srand(
        unsigned( std::time( 0 ) ) );

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
        // Reserving the known number of robots avoids unnecessary vector
        // reallocations while the simulation population is constructed.
        mWallFollowers.reserve(
            mRobotCount );

        mLineFollowers.reserve(
            mRobotCount );

        for( int i = 0; i < mRobotCount; ++i )
        {
            CWallFollower WallRobot(
                mWallMap );

            WallRobot.SetPose(
                MakeNoisyPose(
                    mWallMap.GetStartPose() ) );

            WallRobot.EnableMovementNoise(
                mWheelMovementNoiseFraction );

            mWallFollowers.push_back(
                WallRobot );

            CLineFollower LineRobot(
                mLineMap );

            LineRobot.SetPose(
                MakeNoisyPose(
                    mLineMap.GetStartPose() ) );

            LineRobot.EnableMovementNoise(
                mWheelMovementNoiseFraction );

            mLineFollowers.push_back(
                LineRobot );
        }
    }
    else
    {
        std::cout
            << "CSimulation: failed to load one or more maps"
            << std::endl;
    }
}

//-----------------------------------------------------------------------------
float CSimulation::RandomOffset(
    float aMagnitude ) const
{
    float UnitRandom =
        float( std::rand() )
        / float( RAND_MAX );

    float Offset =
        ( 2.0f * UnitRandom - 1.0f )
        * aMagnitude;

    return Offset;
}

//-----------------------------------------------------------------------------
CPose CSimulation::MakeNoisyPose(
    const CPose& aBasePose ) const
{
    CPose NoisyPose =
        aBasePose;

    // Position and orientation perturbations are independent for every robot.
    NoisyPose.mPosition.x +=
        RandomOffset(
            mStartPositionNoise );

    NoisyPose.mPosition.y +=
        RandomOffset(
            mStartPositionNoise );

    NoisyPose.mHeading +=
        RandomOffset(
            mStartHeadingNoise );

    return NoisyPose;
}

//-----------------------------------------------------------------------------
void CSimulation::Run()
{
    if( mMapsLoaded )
    {
        while( !mRender.WindowShouldClose() )
        {
            Update(
                mFixedDt );

            Render();

            // Press S after most trajectories have completed the circuit to
            // capture the spread required as evidence for the A5 report.
            if( mRender.ScreenshotRequested() )
            {
                mRender.SaveScreenshot(
                    "A5_NoiseSimulation_Final.png" );

                std::cout
                    << "Screenshot saved as A5_NoiseSimulation_Final.png"
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
    // Every robot receives one update per simulation cycle using the same fixed
    // simulated timestep, while its wheel perturbations remain independent.
    for( CWallFollower& Robot : mWallFollowers )
    {
        Robot.Update(
            aDt );
    }

    for( CLineFollower& Robot : mLineFollowers )
    {
        Robot.Update(
            aDt );
    }

    ++mTotalUpdates;
}

//-----------------------------------------------------------------------------
void CSimulation::Render()
{
    mRender.BeginDrawing();

    mWallMap.Draw(
        mRender,
        CRender::COLOUR_WHITE,
        mWallThickness );

    mLineMap.Draw(
        mRender,
        CRender::COLOUR_GREY,
        mLineThickness );

    for( CWallFollower& Robot : mWallFollowers )
    {
        Robot.Draw(
            mRender );
    }

    for( CLineFollower& Robot : mLineFollowers )
    {
        Robot.Draw(
            mRender );
    }

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
        << "Wall followers: "
        << mWallFollowers.size()
        << std::endl;

    std::cout
        << "Line followers: "
        << mLineFollowers.size()
        << std::endl;
}