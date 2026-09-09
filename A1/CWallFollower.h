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
// CWallFollower controls a robot using one right-facing range sensor and one
// forward-right range sensor. It converts their measurements into differential
// wheel speeds and records separate wall-collision events.
//
// The map is stored by reference rather than owned because CSimulation owns
// the map for the complete lifetime of the wall follower.
//-----------------------------------------------------------------------------
class CWallFollower : public CRobot
{
    public:

        // Constructs a wall follower that senses and checks collisions against
        // arMap. The supplied map must outlive this robot.
        CWallFollower( const CMap& arMap );

        // Performs one sensing/control step, moves the robot using aDt and then
        // checks whether a new collision event has begun.
        void Update( float aDt );

        // Returns the number of separate wall-collision events detected.
        int GetCollisionCount() const;

    private:

        // Named sensor indices describe the two required sensor roles.
        enum ESensor
        {
            SENSOR_RIGHT = 0,
            SENSOR_FORWARD_RIGHT,
            NUM_SENSORS
        };

        // Reads both range sensors and converts their measurements into left
        // and right wheel commands.
        void Steer();

        // Detects the beginning of a wall contact and counts each continuous
        // collision only once.
        void CheckCollision();

        // Non-owning reference to the room geometry.
        const CMap& mMap;

        // Exactly two range sensors are owned by the wall follower.
        CRangeSensor mSensors[NUM_SENSORS];

        // Required sensor mounting angles in radians.
        const float mRightSensorAngle{ 1.57079633f };
        const float mForwardRightSensorAngle{ 0.78539816f };

        // Nominal forward wheel speed.
        const float mBaseSpeed{ 80.0f };

        // Desired distance from the right-hand wall.
        const float mTargetWallDistance{ 60.0f };

        // Proportional correction gain for right-wall distance error.
        const float mKp{ 0.6f };

        // Additional turn gain applied when approaching a corner.
        const float mKTurn{ 0.8f };

        // Forward-right distance below which stronger corner avoidance begins.
        const float mForwardRightThreshold{ 80.0f };

        // Number of separate collision events during the current run.
        int mCollisionCount{ 0 };

        // Records whether the preceding update was already in wall contact.
        bool mWasColliding{ false };
};

#endif