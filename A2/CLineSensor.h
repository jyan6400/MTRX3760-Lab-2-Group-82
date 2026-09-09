#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CLoopReader.h"

class CMap;

// CLineSensor models a floor sensor mounted at a fixed position relative to
// the robot. It reports whether the floor directly beneath it contains line.
class CLineSensor
{
    public:
        // Sets the sensor's mounting position relative to the robot centre.
        // x is forward and y is to the robot's right.
        void Mount( const Vec2D& aOffset );

        // Returns true when the floor beneath the sensor is part of the line.
        bool IsOnLine(
            const CPose& aRobotPose,
            const CMap& aMap ) const;

    private:
        Vec2D mOffset{ 0.0f, 0.0f };
};

#endif