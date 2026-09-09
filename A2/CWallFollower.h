/*
 * CWallFollower.h
 *
 * This file declares CWallFollower, a specialised CRobot that follows the
 * wall on its right-hand side using exactly two range sensors.
 */

#ifndef CWALLFOLLOWER_H
#define CWALLFOLLOWER_H

#include "CMap.h"
#include "CRangeSensor.h"
#include "CRobot.h"

//-----------------------------------------------------------------------------
// CWallFollower
//
// CWallFollower controls a robot using one right-facing and one forward-right
// range sensor. It converts their measurements into differential wheel speeds
// and records separate wall-collision events.
//
// The map is stored by reference because CSimulation owns it for the complete
// lifetime of the wall follower.
//-----------------------------------------------------------------------------
class CWallFollower : public CRobot
{
    public:

        // Constructs a wall follower that senses and checks collisions against
        // arMap. The supplied map must outlive the robot.
        CWallFollower( const CMap& arMap );

        // Performs one wall-follower sensing/control step, moves the robot and
        // then checks for a new collision event.
        void Update( float aDt );

        // Returns the number of separate wall-collision events detected.
        int GetCollisionCount() const;

    private:

        // Named indices describe the roles of the two required range sensors.
        enum ESensor
        {
            SENSOR_RIGHT = 0,
            SENSOR_FORWARD_RIGHT,
            NUM_SENSORS
        };

        // Reads the two sensors and converts the measurements into wheel
        // commands.
        void Steer();

        // Counts the beginning of each continuous wall-contact event once.
        void CheckCollision();

        // Non-owning reference to the wall map.
        const CMap& mMap;

        // Exactly two range sensors are owned by the wall follower.
        CRangeSensor mSensors[NUM_SENSORS];

        // Required mounting directions, stored in radians.
        const float mRightSensorAngle{ 1.57079633f };
        const float mForwardRightSensorAngle{ 0.78539816f };

        // Nominal forward wheel speed.
        const float mBaseSpeed{ 80.0f };

        // Desired distance from the right-hand wall.
        const float mTargetWallDistance{ 60.0f };

        // Proportional correction gain for wall-distance error.
        const float mKp{ 0.6f };

        // Additional turn gain used when approaching a corner.
        const float mKTurn{ 0.8f };

        // Forward-right range below which stronger corner avoidance begins.
        const float mForwardRightThreshold{ 80.0f };

        // Number of separate collision events detected.
        int mCollisionCount{ 0 };

        // Indicates whether the previous update was already in wall contact.
        bool mWasColliding{ false };
};

#endif