/*
 * CRangeSensor.h
 *
 * This file declares CRangeSensor, which models a range sensor mounted at a
 * fixed angular offset from a robot and reports the distance to the first map
 * segment intersected by its sensing ray.
 */

#ifndef CRANGESENSOR_H
#define CRANGESENSOR_H

#include "CRender.h"

class CMap;

//-----------------------------------------------------------------------------
// CRangeSensor
//
// CRangeSensor represents one robot-mounted range sensor. Its mounting angle
// is stored relative to the robot heading. When queried, it converts this to a
// world-space ray and asks CMap for the nearest segment intersection.
//-----------------------------------------------------------------------------
class CRangeSensor
{
    public:

        // Sets the sensor mounting angle relative to the robot heading.
        // aAngleOffset is specified in radians.
        void Mount( float aAngleOffset );

        // Returns the distance from the robot position to the nearest map
        // segment intersected by this sensor's forward ray.
        float GetDistance(
            const Vec2D& aRobotPosition,
            float aRobotHeading,
            const CMap& aMap ) const;

    private:

        // Angular mounting offset relative to the robot heading, in radians.
        float mAngleOffset{ 0.0f };
};

#endif