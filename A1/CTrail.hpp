// CTrail is the class responsible for storing all the historical coordinate points 
// that the robot has passed through, and drawing continuous trail segments. 
#ifndef CTRAIL_HPP
#define CTRAIL_HPP

#include <vector>
#include "CRender.h"


class CTrail
{
public:
    // Record the current coordinate of the robot
    void AddPoint( const Vec2D& aPosition );

    // Draw the trail by drawing line segments
    void Draw( CRender& aRender ) const;

private:
    // Store the coordinate of the historical trail
    std::vector<Vec2D> mPoints; 
};

#endif