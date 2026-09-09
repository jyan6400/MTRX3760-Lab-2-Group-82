#include "CLineSensor.h"

#include "CMap.h"

#include <cmath>

void CLineSensor::Mount( const Vec2D& aOffset )
{
    mOffset = aOffset;
}

bool CLineSensor::IsOnLine(
    const CPose& aRobotPose,
    const CMap& aMap ) const
{
    float CosHeading =
        std::cos( aRobotPose.mHeading );

    float SinHeading =
        std::sin( aRobotPose.mHeading );

    // Transform the sensor's robot-relative mounting position into
    // world coordinates.
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
        aMap.IsPointOnLine( SensorPosition );

    return OnLine;
}