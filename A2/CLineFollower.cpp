#include "CLineFollower.h"

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

void CLineFollower::Update( float aDt )
{
    Steer();
    Move( aDt );
}

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

    if( LineSensorOn && !SideSensorOn )
    {
        // Desired state: the main sensor is over the line while the
        // side sensor remains beside it.
        LeftSpeed =
            mBaseSpeed;

        RightSpeed =
            mBaseSpeed;
    }
    else if( !LineSensorOn && SideSensorOn )
    {
        // The line has moved towards the right-side sensor, so steer right.
        LeftSpeed =
            mBaseSpeed + mTurnAmount;

        RightSpeed =
            mBaseSpeed - mTurnAmount;
    }
    else if( !LineSensorOn && !SideSensorOn )
    {
        // Both sensors are off the line on the same side, so steer left
        // to recover the desired sensor arrangement.
        LeftSpeed =
            mBaseSpeed - mTurnAmount;

        RightSpeed =
            mBaseSpeed + mTurnAmount;
    }
    else
    {
        // Both sensors are over the line. Continue forward until the
        // normal one-on/one-off arrangement is recovered.
        LeftSpeed =
            mBaseSpeed;

        RightSpeed =
            mBaseSpeed;
    }

    SetWheelSpeeds(
        LeftSpeed,
        RightSpeed );
}