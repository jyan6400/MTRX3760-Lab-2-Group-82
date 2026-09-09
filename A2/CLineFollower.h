#ifndef CLINEFOLLOWER_H
#define CLINEFOLLOWER_H

#include "CLineSensor.h"
#include "CMap.h"
#include "CRobot.h"

// CLineFollower is a CRobot that follows the floor line using exactly two
// line sensors. One sensor normally sits over the line while the second sits
// to its right, allowing the robot to correct its position using sensor state.
class CLineFollower : public CRobot
{
    public:
        // Creates a line follower that senses the supplied line map.
        CLineFollower( const CMap& arLineMap );

        // Performs one sensing, control and movement update.
        void Update( float aDt );

    private:
        enum ESensor
        {
            SENSOR_LINE = 0,
            SENSOR_SIDE,
            NUM_SENSORS
        };

        // Reads both line sensors and converts their states into wheel speeds.
        void Steer();

        // The robot knows the line map but does not own it.
        const CMap& mLineMap;

        CLineSensor mSensors[NUM_SENSORS];

        // Both sensors are mounted slightly in front of the robot.
        // The second sensor is offset to the robot's right.
        const Vec2D mLineSensorOffset{ 8.0f, 0.0f };
        const Vec2D mSideSensorOffset{ 8.0f, 5.0f };

        const float mBaseSpeed{ 60.0f };
        const float mTurnAmount{ 35.0f };
};

#endif