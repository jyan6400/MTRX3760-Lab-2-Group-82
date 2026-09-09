/*
 * CLineSensor.cpp
 *
 * This file implements CLineSensor by transforming its robot-local mounting
 * position into world coordinates before querying the line map.
 */

#include "CLineSensor.h"

#include "CMap.h"

#include <cmath>

//-----------------------------------------------------------------------------
void CLineSensor::Mount( const Vec2D& aOffset )
{
    mOffset =
        aOffset;
}

//-----------------------------------------------------------------------------
bool CLineSensor::IsOnLine(
    const CPose& aRobotPose,
    const CMap& aMap ) const
{
    float CosHeading =
        std::cos( aRobotPose.mHeading );

    float SinHeading =
        std::sin( aRobotPose.mHeading );

    // Rotate the local sensor offset by the current robot heading, then
    // translate it by the robot position to obtain world coordinates.
    Vec2D SensorPosition
    {
        aRobotPose.mPosition.x
            + mOffset.x * CosHeading
            - mOffset.y * SinHeading,

        aRobotPose.mPosition.y
            + mOffset.x * SinHeading
            + mOffset.y * CosHeading
    };

    bool OnLine =
        aMap.IsPointOnLine(
            SensorPosition );

    return OnLine;
}