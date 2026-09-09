#include "CSimulation.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

CSimulation::CSimulation(
    const std::string& aWallMapFilename,
    const std::string& aLineMapFilename )
    :
        mWallMap(),
        mLineMap()
{
    // Seed the random-number generator once for the whole simulation.
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
        // Reserving first prevents unnecessary vector reallocations while
        // constructing the fixed set of 20 robots of each type.
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

CPose CSimulation::MakeNoisyPose(
    const CPose& aBasePose ) const
{
    CPose NoisyPose =
        aBasePose;

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
    for( CWallFollower& Robot :
         mWallFollowers )
    {
        Robot.Update(
            aDt );
    }

    for( CLineFollower& Robot :
         mLineFollowers )
    {
        Robot.Update(
            aDt );
    }

    ++mTotalUpdates;
}

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

    for( CWallFollower& Robot :
         mWallFollowers )
    {
        Robot.Draw(
            mRender );
    }

    for( CLineFollower& Robot :
         mLineFollowers )
    {
        Robot.Draw(
            mRender );
    }

    mRender.EndDrawing();
}

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