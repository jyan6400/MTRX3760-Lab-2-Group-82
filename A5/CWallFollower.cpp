/*
 * CWallFollower.cpp
 *
 * This file implements the wall-following controller and collision-event
 * detection used by each A5 wall follower.
 */

#include "CWallFollower.h"

#include <iostream>

//-----------------------------------------------------------------------------
CWallFollower::CWallFollower(
    const CMap& arMap )
    :
        mMap( arMap )
{
    mSensors[SENSOR_RIGHT].Mount(
        mRightSensorAngle );

    mSensors[SENSOR_FORWARD_RIGHT].Mount(
        mForwardRightSensorAngle );
}

//-----------------------------------------------------------------------------
void CWallFollower::Update( float aDt )
{
    Steer();

    Move(
        aDt );

    CheckCollision();
}

//-----------------------------------------------------------------------------
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

    // Positive error means the robot is farther from the right wall than the
    // target distance; negative error means it is too close.
    float Error =
        RightDistance
        - mTargetWallDistance;

    float TurnRate =
        mKp * Error;

    // Increase the corrective turn when an approaching wall or corner enters
    // the forward-right sensing threshold.
    if( ForwardRightDistance < mForwardRightThreshold )
    {
        TurnRate -=
            mKTurn
            * ( mForwardRightThreshold
                - ForwardRightDistance );
    }

    SetWheelSpeeds(
        mBaseSpeed - TurnRate,
        mBaseSpeed + TurnRate );
}

//-----------------------------------------------------------------------------
void CWallFollower::CheckCollision()
{
    bool IsColliding =
        mMap.CheckCollision(
            GetPose().mPosition,
            GetRadius() );

    // Count only the transition into contact so a continuous collision is
    // represented by one event rather than many simulation updates.
    if( IsColliding && !mWasColliding )
    {
        ++mCollisionCount;

        std::cout
            << "CWallFollower: collision detected (total "
            << mCollisionCount
            << ")"
            << std::endl;
    }

    mWasColliding =
        IsColliding;
}

//-----------------------------------------------------------------------------
int CWallFollower::GetCollisionCount() const
{
    return mCollisionCount;
}