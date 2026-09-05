#include <cmath>
#include <iostream>
#include "CWallFollower.hpp"

const float Pi = 3.14159265f;
const float HalfCircle = 180.0f;
const float kDegreesToRadians = Pi / HalfCircle;

CWallFollower::CWallFollower( const CMap& arMap )
    :
        mMap( arMap )
{
    mSensors[0].Mount( 90.0f * kDegreesToRadians );   // straight right
    mSensors[1].Mount( 45.0f * kDegreesToRadians );   // forward-right
}

void CWallFollower::Update( float aDt )
{
    Steer();
    Move( aDt );
    CheckCollision();
}

void CWallFollower::Steer()
{
    // Obtain the distance of the wall measured by the two sensors
    float RightDistance = mSensors[0].GetDistance( GetPose().mPosition, GetPose().mHeading, mMap );
    float FrontDistance = mSensors[1].GetDistance( GetPose().mPosition, GetPose().mHeading, mMap );

    // Calculate the deviation of the distance on the right side
    float Error = RightDistance - mTargetWallDistance;
    
    // Calculate the steering deflection based on the deviation
    float TurnRate = mKp * Error;

    // Turn when it's close to the wall
    if( FrontDistance < mFrontThreshold )
    {
        TurnRate -= mKTurn * ( mFrontThreshold - FrontDistance );
    }

    mWheels[0].SetSpeed( mBaseSpeed - TurnRate );   // left wheel
    mWheels[1].SetSpeed( mBaseSpeed + TurnRate );   // right wheel
}

void CWallFollower::CheckCollision()
{
    if( mMap.CheckCollision( GetPose().mPosition, GetRadius() ) )
    {
        ++mCollisionCount;
        std::cout << "CWallFollower: collision detected (total " << mCollisionCount << ")" << std::endl;
    }
}

int CWallFollower::GetCollisionCount() const
{
    return mCollisionCount;
}