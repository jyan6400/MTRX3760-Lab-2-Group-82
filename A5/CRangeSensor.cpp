#include "CRangeSensor.h"
#include "CMap.h"

void CRangeSensor::Mount( float aAngleOffset )
{
    mAngleOffset = aAngleOffset;
}

float CRangeSensor::GetDistance(
    const Vec2D& aRobotPosition,
    float aRobotHeading,
    const CMap& aMap ) const
{
    float MapAngle = aRobotHeading + mAngleOffset;
    float Distance = aMap.GetRayIntersection( aRobotPosition, MapAngle );

    return Distance;
}