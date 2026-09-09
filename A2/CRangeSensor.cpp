/*
 * CRangeSensor.cpp
 *
 * This file implements CRangeSensor by converting the sensor's robot-relative
 * mounting angle into a world-space ray before querying CMap.
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
    // Combine robot heading and sensor mounting angle to obtain the direction
    // of the sensing ray in world coordinates.
    float MapAngle =
        aRobotHeading + mAngleOffset;

    float Distance =
        aMap.GetRayIntersection(
            aRobotPosition,
            MapAngle );

    return Distance;
}