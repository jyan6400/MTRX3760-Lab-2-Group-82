#ifndef CRANGESENSOR_H
#define CRANGESENSOR_H

#include "CRender.h"

class CMap;

// CRangeSensor models one range sensor mounted at a fixed angular offset from
// the robot heading. It reports the distance to the first wall its ray meets.
class CRangeSensor
{
    public:
        // Sets the mounting angle relative to the robot heading.
        void Mount( float aAngleOffset );

        // Returns the distance from the robot to the first wall hit by the
        // sensor ray.
        float GetDistance(
            const Vec2D& aRobotPosition,
            float aRobotHeading,
            const CMap& aMap ) const;

    private:
        float mAngleOffset{ 0.0f };
};

#endif