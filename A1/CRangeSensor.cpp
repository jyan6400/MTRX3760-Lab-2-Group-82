#include "CRangeSensor.hpp"
#include "CMap.hpp"

void CRangeSensor::Mount( float aAngleOffset )
{
    mAngleOffset = aAngleOffset;
}


float CRangeSensor::GetDistance( const Vec2D& aRobotPosition, float aRobotHeading, const CMap& aMap ) const
{
    float MapAngle = aRobotHeading + mAngleOffset;
    
    // Obtain the distance by using the map intersection method
    return aMap.GetRayIntersection( aRobotPosition, MapAngle );
}