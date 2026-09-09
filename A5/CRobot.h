#ifndef CROBOT_H
#define CROBOT_H

#include "CLoopReader.h"
#include "CRender.h"
#include "CTrail.h"
#include "CWheel.h"

// CRobot is the abstract base class for simulated robots. It owns the common
// pose, two independently controlled wheels and permanent trail, and implements
// differential-drive movement and drawing shared by derived robot types.
class CRobot
{
    public:
        virtual ~CRobot() = default;

        // Sets the robot's position and heading.
        void SetPose( const CPose& aPose );

        // Returns the robot's current position and heading.
        const CPose& GetPose() const;

        // Returns the robot's collision radius.
        float GetRadius() const;

        // Enables random variation in each wheel's movement per timestep.
        void EnableMovementNoise( float aNoiseFraction );

        // Each derived robot provides its own sensing and control behaviour.
        virtual void Update( float aDt ) = 0;

        // Draws the permanent trail, robot body and heading indicator.
        void Draw( CRender& aRender ) const;

    protected:
        enum EWheel
        {
            WHEEL_LEFT = 0,
            WHEEL_RIGHT,
            NUM_WHEELS
        };

        // Advances the differential-drive motion model by one timestep.
        void Move( float aDt );

        // Commands the two wheels independently.
        void SetWheelSpeeds(
            float aLeftSpeed,
            float aRightSpeed );

    private:
        // Returns a random value in the range [-aMagnitude, +aMagnitude].
        float RandomOffset( float aMagnitude ) const;

        CPose mPose{ { 0.0f, 0.0f }, 0.0f };

        CWheel mWheels[NUM_WHEELS];

        CTrail mTrail;

        const float mRadius{ 15.0f };
        const float mWheelBase{ 20.0f };
        const float mHeadingLineThickness{ 2.0f };

        bool mMovementNoiseEnabled{ false };
        float mMovementNoiseFraction{ 0.0f };
};

#endif