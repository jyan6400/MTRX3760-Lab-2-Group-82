/*
 * CRobot.h
 *
 * This file declares the abstract CRobot base class containing behaviour
 * common to both noisy robot types. It also provides the A5 wheel-movement
 * perturbation used to create different trajectories between nominally
 * identical robots.
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
// CRobot is the common base class for the wall-following and line-following
// robots. Derived classes provide sensing and control, while CRobot owns the
// pose, exactly two wheels, permanent trail and differential-drive model.
//
// For A5, CRobot can independently perturb the distance travelled by each
// wheel during every simulated timestep.
//-----------------------------------------------------------------------------
class CRobot
{
    public:

        // Ensures derived robot objects are destroyed correctly through the
        // abstract CRobot interface.
        virtual ~CRobot() = default;

        // Sets the robot's complete world-space pose.
        void SetPose( const CPose& aPose );

        // Returns the current robot pose without creating a copy.
        const CPose& GetPose() const;

        // Returns the physical collision radius of the robot.
        float GetRadius() const;

        // Enables independent random wheel-travel perturbations. The supplied
        // value is the maximum fractional deviation from nominal travel.
        void EnableMovementNoise( float aNoiseFraction );

        // Performs one robot-specific sensing and control update.
        virtual void Update( float aDt ) = 0;

        // Draws the permanent trail, circular body and heading indicator.
        void Draw( CRender& aRender ) const;

    protected:

        // Named indices identify the two independently controlled wheels.
        enum EWheel
        {
            WHEEL_LEFT = 0,
            WHEEL_RIGHT,
            NUM_WHEELS
        };

        // Advances the differential-drive model using the current wheel
        // commands and supplied simulated timestep.
        void Move( float aDt );

        // Commands the two wheels independently.
        void SetWheelSpeeds(
            float aLeftSpeed,
            float aRightSpeed );

    private:

        // Returns a uniformly distributed random value in
        // [-aMagnitude, +aMagnitude].
        float RandomOffset( float aMagnitude ) const;

        // Current position and heading in world coordinates.
        CPose mPose{ { 0.0f, 0.0f }, 0.0f };

        // Exactly two independently controlled wheels belong to every robot.
        CWheel mWheels[NUM_WHEELS];

        // Permanent trajectory belonging to this robot.
        CTrail mTrail;

        // Physical radius of the robot body.
        const float mRadius{ 15.0f };

        // Separation used by the differential-drive kinematic model.
        const float mWheelBase{ 20.0f };

        // Visual thickness of the heading indicator.
        const float mHeadingLineThickness{ 2.0f };

        // Controls whether A5 wheel-movement perturbation is active.
        bool mMovementNoiseEnabled{ false };

        // Maximum fractional change to each wheel's nominal travel per update.
        float mMovementNoiseFraction{ 0.0f };
};

#endif