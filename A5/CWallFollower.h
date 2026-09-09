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
// CWallFollower uses one right-facing and one forward-right range sensor to
// determine its two wheel commands. In A5 the controller remains unchanged;
// trajectory variation is introduced by the CRobot movement model.
//
// The map is stored by reference because CSimulation owns it for the complete
// lifetime of every wall follower.
//-----------------------------------------------------------------------------
class CWallFollower : public CRobot
{
    public:

        // Constructs a wall follower that senses and checks collisions against
        // arMap. The supplied map must outlive this robot.
        CWallFollower( const CMap& arMap );

        // Performs one sensing/control step, advances the robot and checks for
        // a new wall-collision event.
        void Update( float aDt );

        // Returns the number of separate collision events detected.
        int GetCollisionCount() const;

    private:

        // Named indices describe the roles of the two required range sensors.
        enum ESensor
        {
            SENSOR_RIGHT = 0,
            SENSOR_FORWARD_RIGHT,
            NUM_SENSORS
        };

        // Reads the two sensors and converts their distances into wheel speeds.
        void Steer();

        // Counts the beginning of each continuous wall contact once.
        void CheckCollision();

        // Non-owning reference to the wall map.
        const CMap& mMap;

        // Exactly two range sensors are owned by each wall follower.
        CRangeSensor mSensors[NUM_SENSORS];

        // Required sensor mounting directions, in radians.
        const float mRightSensorAngle{ 1.57079633f };
        const float mForwardRightSensorAngle{ 0.78539816f };

        // Nominal wall-following controller parameters.
        const float mBaseSpeed{ 80.0f };
        const float mTargetWallDistance{ 60.0f };
        const float mKp{ 0.6f };
        const float mKTurn{ 0.8f };
        const float mForwardRightThreshold{ 80.0f };

        // Number of separate collision events detected by this robot.
        int mCollisionCount{ 0 };

        // Prevents one continuous contact from being counted every update.
        bool mWasColliding{ false };
};

#endif