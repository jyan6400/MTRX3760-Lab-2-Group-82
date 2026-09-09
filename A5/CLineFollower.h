/*
 * CLineFollower.h
 *
 * This file declares CLineFollower, a specialised CRobot that follows the
 * five-unit-wide floor line using exactly two line sensors.
 */

#ifndef CLINEFOLLOWER_H
#define CLINEFOLLOWER_H

#include "CLineSensor.h"
#include "CMap.h"
#include "CRobot.h"

//-----------------------------------------------------------------------------
// CLineFollower
//
// CLineFollower uses exactly two Boolean line sensors. One normally sits over
// the target line while the second is positioned to its side. Their states are
// converted into independent wheel commands.
//
// In A5 the line controller is unchanged; random physical movement causes the
// nominally identical robots to follow visibly different trajectories.
//-----------------------------------------------------------------------------
class CLineFollower : public CRobot
{
    public:

        // Constructs a line follower that senses arLineMap. The supplied map
        // must outlive this robot.
        CLineFollower( const CMap& arLineMap );

        // Performs one line-sensing/control step and advances the robot using
        // the supplied simulated timestep.
        void Update( float aDt );

    private:

        // Named indices identify the roles of the two required line sensors.
        enum ESensor
        {
            SENSOR_LINE = 0,
            SENSOR_SIDE,
            NUM_SENSORS
        };

        // Reads both line sensors and selects the corresponding wheel speeds.
        void Steer();

        // Non-owning reference to the floor-line geometry.
        const CMap& mLineMap;

        // Exactly two line sensors are owned by each line follower.
        CLineSensor mSensors[NUM_SENSORS];

        // Robot-local sensor offsets: x is forward and y is right.
        const Vec2D mLineSensorOffset{ 8.0f, 0.0f };
        const Vec2D mSideSensorOffset{ 8.0f, 5.0f };

        // Nominal line-following controller parameters.
        const float mBaseSpeed{ 60.0f };
        const float mTurnAmount{ 35.0f };
};

#endif