// CRanageSensor is the class responsible for controlling angle offset
//  (e.g. 90 degrees for straight right, 45 degrees for
// forward-right). It reports the distance to the first wall its ray meets.
#ifndef CRANGESENSOR_HPP
#define CRANGESENSOR_HPP

#include "CRender.h"

class CMap;

class CRangeSensor
{
public:
    // Set the angle of the sensor relative to the robot
    void Mount( float aAngleOffset );

    // Calculate the distance at which the ray first hits the wall
    float GetDistance( const Vec2D& aRobotPosition, float aRobotHeading, const CMap& aMap ) const;

private:
    // The current angle of the sensor relative to the robot
    float mAngleOffset{ 0.0f }; 
};

#endif