/*
 * CLineSensor.h
 *
 * This file declares CLineSensor, which models a line detector mounted at a
 * fixed local position on a robot and reports whether that point lies over
 * the floor line.
 */

#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CLoopReader.h"

class CMap;

//-----------------------------------------------------------------------------
// CLineSensor
//
// CLineSensor represents one point sensor attached to a line-following robot.
// Its mounting location is expressed in robot-local coordinates. The sensor
// transforms that point into world coordinates before querying CMap.
//-----------------------------------------------------------------------------
class CLineSensor
{
    public:

        // Sets the sensor position relative to the robot centre. Positive x is
        // forward and positive y is toward the robot's right-hand side.
        void Mount( const Vec2D& aOffset );

        // Returns true when the sensor's current world-space position lies
        // over the five-unit-wide line represented by aMap.
        bool IsOnLine(
            const CPose& aRobotPose,
            const CMap& aMap ) const;

    private:

        // Sensor position relative to the robot centre.
        Vec2D mOffset{ 0.0f, 0.0f };
};

#endif