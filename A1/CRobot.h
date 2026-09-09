/*
 * CRobot.h
 *
 * This file declares the abstract CRobot base class containing the state and
 * behaviour common to simulated robot types, including pose, two wheels,
 * differential-drive movement, permanent trail storage and rendering.
 */

#ifndef CROBOT_H
#define CROBOT_H

#include "CLoopReader.h"
#include "CRender.h"
#include "CTrail.h"
#include "CWheel.h"

//-----------------------------------------------------------------------------
// CRobot
//
// CRobot is the common base class for simulated robots. Derived classes decide
// how sensor readings are converted into wheel commands, while CRobot owns and
// operates the shared physical state and differential-drive motion model.
//-----------------------------------------------------------------------------
class CRobot
{
    public:

        // Ensures derived robot objects are destroyed correctly through the
        // abstract CRobot interface.
        virtual ~CRobot() = default;

        // Sets the robot's complete world-space pose.
        void SetPose( const CPose& aPose );

        // Returns the robot's current pose without creating a copy.
        const CPose& GetPose() const;

        // Returns the collision radius of the robot.
        float GetRadius() const;

        // Performs one robot-specific sensing and control update.
        virtual void Update( float aDt ) = 0;

        // Draws the permanent trail, circular robot body and heading indicator.
        void Draw( CRender& aRender ) const;

    protected:

        // Named indices identify the two independently controlled wheels.
        enum EWheel
        {
            WHEEL_LEFT = 0,
            WHEEL_RIGHT,
            NUM_WHEELS
        };

        // Advances the differential-drive model using the current wheel speeds
        // and the supplied simulated timestep.
        void Move( float aDt );

        // Sets the independently commanded left and right wheel speeds.
        void SetWheelSpeeds(
            float aLeftSpeed,
            float aRightSpeed );

    private:

        // Current world-space position and heading.
        CPose mPose{ { 0.0f, 0.0f }, 0.0f };

        // Exactly two wheels are owned by every robot.
        CWheel mWheels[NUM_WHEELS];

        // Permanent trajectory belonging to this robot.
        CTrail mTrail;

        // Robot radius required by the A1 specification.
        const float mRadius{ 15.0f };

        // Separation used by the differential-drive kinematic model.
        const float mWheelBase{ 20.0f };

        // Visual thickness of the robot heading indicator.
        const float mHeadingLineThickness{ 2.0f };
};

#endif