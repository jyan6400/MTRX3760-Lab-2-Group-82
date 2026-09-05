#include <iostream>
#include "CSimulation.hpp"

CSimulation::CSimulation( const std::string& aFilename )
  : mMap(),
    mRobot( mMap )
{
    bool Loaded = mMap.Load( aFilename );
    if( Loaded )
    {
        mRobot.SetPose( mMap.GetStartPose() );
    }
    else
    {
        std::cout << "CSimulation: failed to load map '" << aFilename << "'" << std::endl;
    }
}

void CSimulation::Run()
{
    while( !mRender.WindowShouldClose() )
    {
        Update( mFixedDt );
        Render();
    }

    mRender.CloseWindow();
    Report();
}

void CSimulation::Update( float aDt )
{
    mRobot.Update( aDt );
    ++mTotalUpdates;
}

void CSimulation::Render()
{
    mRender.BeginDrawing();
    mMap.Draw( mRender );
    mRobot.Draw( mRender );
    mRender.EndDrawing();
}

void CSimulation::Report() const
{
    std::cout << "Total updates: " << mTotalUpdates << std::endl;
    std::cout << "Total collisions: " << mRobot.GetCollisionCount() << std::endl;
}