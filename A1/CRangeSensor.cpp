/*
 * CRangeSensor.cpp
 *
 * This file implements CRangeSensor by converting the sensor's robot-relative
 * mounting angle into a world-space ray before querying the map.
 */

#include "CRangeSensor.h"

#include "CMap.h"

//-----------------------------------------------------------------------------
void CRangeSensor::Mount( float aAngleOffset )
{
    mAngleOffset = aAngleOffset;
}

//-----------------------------------------------------------------------------
float CRangeSensor::GetDistance(
    const Vec2D& aRobotPosition,
    float aRobotHeading,
    const CMap& aMap ) const
{
    // Combine the robot heading and mounting offset to obtain the sensor's
    // direction in world coordinates.
    float MapAngle =
        aRobotHeading + mAngleOffset;

    float Distance =
        aMap.GetRayIntersection(
            aRobotPosition,
            MapAngle );

    return Distance;
}