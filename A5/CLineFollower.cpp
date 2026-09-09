/*
 * CLineFollower.cpp
 *
 * This file implements the two-sensor line-following controller used by each
 * A5 line follower.
 */

#include "CLineFollower.h"

//-----------------------------------------------------------------------------
CLineFollower::CLineFollower(
    const CMap& arLineMap )
    :
        mLineMap( arLineMap )
{
    mSensors[SENSOR_LINE].Mount(
        mLineSensorOffset );

    mSensors[SENSOR_SIDE].Mount(
        mSideSensorOffset );
}

//-----------------------------------------------------------------------------
void CLineFollower::Update( float aDt )
{
    Steer();

    Move(
        aDt );
}

//-----------------------------------------------------------------------------
void CLineFollower::Steer()
{
    bool LineSensorOn =
        mSensors[SENSOR_LINE].IsOnLine(
            GetPose(),
            mLineMap );

    bool SideSensorOn =
        mSensors[SENSOR_SIDE].IsOnLine(
            GetPose(),
            mLineMap );

    float LeftSpeed =
        mBaseSpeed;

    float RightSpeed =
        mBaseSpeed;

    // Normal tracking has the main sensor over the line and side sensor off it.
    if( LineSensorOn && !SideSensorOn )
    {
        LeftSpeed =
            mBaseSpeed;

        RightSpeed =
            mBaseSpeed;
    }
    else if( !LineSensorOn && SideSensorOn )
    {
        // The line has moved toward the side sensor, so steer right.
        LeftSpeed =
            mBaseSpeed + mTurnAmount;

        RightSpeed =
            mBaseSpeed - mTurnAmount;
    }
    else if( !LineSensorOn && !SideSensorOn )
    {
        // Neither sensor sees the line, so steer back toward the main sensor's
        // normal tracking position.
        LeftSpeed =
            mBaseSpeed - mTurnAmount;

        RightSpeed =
            mBaseSpeed + mTurnAmount;
    }
    else
    {
        // When both sensors overlap the line, continue forward until the
        // geometry produces an unambiguous correction.
        LeftSpeed =
            mBaseSpeed;

        RightSpeed =
            mBaseSpeed;
    }

    SetWheelSpeeds(
        LeftSpeed,
        RightSpeed );
}