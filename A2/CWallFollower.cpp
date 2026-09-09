/*
 * CWallFollower.cpp
 *
 * This file implements the wall-following controller, required range-sensor
 * arrangement and collision-event detection used by CWallFollower.
 */

#include "CWallFollower.h"

#include <iostream>

//-----------------------------------------------------------------------------
CWallFollower::CWallFollower(
    const CMap& arMap )
    :
        mMap( arMap )
{
    // The two mounting directions are fixed by the A1/A2 specification.
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

    // Positive error means the robot is farther from the wall than desired;
    // negative error means it is closer than desired.
    float Error =
        RightDistance
        - mTargetWallDistance;

    float TurnRate =
        mKp * Error;

    // The forward-right sensor increases the turn as an approaching wall or
    // corner enters the chosen threshold.
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

    // Count only the transition into contact so a sustained collision is not
    // counted again on every fixed simulation update.
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