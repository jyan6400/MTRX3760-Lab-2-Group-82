#include "CWallFollower.h"

#include <iostream>

CWallFollower::CWallFollower( const CMap& arMap )
    :
        mMap( arMap )
{
    mSensors[SENSOR_RIGHT].Mount(
        mRightSensorAngle );

    mSensors[SENSOR_FORWARD_RIGHT].Mount(
        mForwardRightSensorAngle );
}

void CWallFollower::Update( float aDt )
{
    Steer();
    Move( aDt );
    CheckCollision();
}

void CWallFollower::Steer()
{
    float RightDistance =
        mSensors[SENSOR_RIGHT].GetDistance(
            GetPose().mPosition,
            GetPose().mHeading,
            mMap );

    float ForwardRightDistance =
        mSensors[SENSOR_FORWARD_RIGHT].GetDistance(
            GetPose().mPosition,
            GetPose().mHeading,
            mMap );

    // Positive error means the robot is too far from the right wall.
    float Error =
        RightDistance - mTargetWallDistance;

    float TurnRate =
        mKp * Error;

    // Add stronger corner avoidance when the forward-right sensor sees
    // a wall inside its threshold.
    if( ForwardRightDistance < mForwardRightThreshold )
    {
        TurnRate -=
            mKTurn
            * ( mForwardRightThreshold - ForwardRightDistance );
    }

    SetWheelSpeeds(
        mBaseSpeed - TurnRate,
        mBaseSpeed + TurnRate );
}

void CWallFollower::CheckCollision()
{
    bool IsColliding =
        mMap.CheckCollision(
            GetPose().mPosition,
            GetRadius() );

    if( IsColliding && !mWasColliding )
    {
        ++mCollisionCount;

        std::cout
            << "CWallFollower: collision detected (total "
            << mCollisionCount
            << ")"
            << std::endl;
    }

    mWasColliding = IsColliding;
}

int CWallFollower::GetCollisionCount() const
{
    return mCollisionCount;
}