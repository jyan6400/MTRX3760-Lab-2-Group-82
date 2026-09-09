#ifndef CWALLFOLLOWER_H
#define CWALLFOLLOWER_H

#include "CMap.h"
#include "CRangeSensor.h"
#include "CRobot.h"

// CWallFollower is a CRobot that follows the wall on its right. It uses one
// right-facing and one forward-right range sensor to calculate differential
// wheel speeds and counts wall-collision events.
class CWallFollower : public CRobot
{
    public:
        // Creates a wall follower that senses and checks collisions against
        // the supplied map.
        CWallFollower( const CMap& arMap );

        // Performs sensing/control, movement and collision detection.
        void Update( float aDt );

        // Returns the number of separate wall-collision events.
        int GetCollisionCount() const;

    private:
        // Named sensor indices make the two required sensor roles explicit.
        enum ESensor
        {
            SENSOR_RIGHT = 0,
            SENSOR_FORWARD_RIGHT,
            NUM_SENSORS
        };

        // Calculates wheel commands from the two range sensor readings.
        void Steer();

        // Detects and counts the start of each wall-collision event.
        void CheckCollision();

        // The wall follower knows the map but does not own it.
        const CMap& mMap;

        CRangeSensor mSensors[NUM_SENSORS];

        // Required range-sensor mounting angles, in radians.
        const float mRightSensorAngle{ 1.57079633f };
        const float mForwardRightSensorAngle{ 0.78539816f };

        // Wall-following controller constants.
        const float mBaseSpeed{ 80.0f };
        const float mTargetWallDistance{ 60.0f };
        const float mKp{ 0.6f };
        const float mKTurn{ 0.8f };
        const float mForwardRightThreshold{ 80.0f };

        int mCollisionCount{ 0 };

        // Prevents one continuous contact from being counted every update.
        bool mWasColliding{ false };
};

#endif