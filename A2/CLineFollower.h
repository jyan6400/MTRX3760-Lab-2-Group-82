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
// CLineFollower controls a robot using exactly two binary line sensors. One
// sensor is positioned over the target line during normal tracking and the
// second is offset to its right. Their Boolean states determine the two wheel
// commands used to remain near the line.
//
// The line map is stored by reference because CSimulation owns it for the
// complete lifetime of the line follower.
//-----------------------------------------------------------------------------
class CLineFollower : public CRobot
{
    public:

        // Constructs a line follower that senses the supplied line map.
        // arLineMap must outlive the robot.
        CLineFollower( const CMap& arLineMap );

        // Performs one line-sensing/control step and advances the robot by the
        // supplied simulated timestep.
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

        // Exactly two line sensors are owned by the line follower.
        CLineSensor mSensors[NUM_SENSORS];

        // Sensor offsets are robot-local: x is forward and y is right.
        const Vec2D mLineSensorOffset{ 8.0f, 0.0f };
        const Vec2D mSideSensorOffset{ 8.0f, 5.0f };

        // Nominal wheel speed during line following.
        const float mBaseSpeed{ 60.0f };

        // Difference applied between wheel speeds when steering.
        const float mTurnAmount{ 35.0f };
};

#endif