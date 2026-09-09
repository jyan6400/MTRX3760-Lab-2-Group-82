/*
 * CLineFollower.cpp
 *
 * This file implements the two-sensor line-following controller used by
 * CLineFollower.
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

    // The four possible binary sensor states provide a simple feedback
    // controller. Normal tracking occurs when the main sensor is on the line
    // and the side sensor is off it.
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
        // Neither sensor currently sees the line, so turn back toward the side
        // on which the main tracking sensor normally sits.
        LeftSpeed =
            mBaseSpeed - mTurnAmount;

        RightSpeed =
            mBaseSpeed + mTurnAmount;
    }
    else
    {
        // If both sensors overlap the five-unit line, continue forward until
        // the sensor arrangement resolves the direction of the next correction.
        LeftSpeed =
            mBaseSpeed;

        RightSpeed =
            mBaseSpeed;
    }

    SetWheelSpeeds(
        LeftSpeed,
        RightSpeed );
}