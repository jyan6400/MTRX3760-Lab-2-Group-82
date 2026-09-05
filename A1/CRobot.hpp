// CRobot is the base class follows requirements specification 
// Utilizes object-oriented pure virtual function design, 
// which can be implemented by subclasses for specific wall-following algorithms.
#ifndef CROBOT_HPP
#define CROBOT_HPP

#include "CRender.h"
#include "CLoopReader.h"
#include "CWheel.hpp"
#include "CTrail.hpp"


class CRobot
{
    public:
        virtual ~CRobot() = default;

        // Set the pose of the robot
        void SetPose( const CPose& aPose );
        
        // Obtain the current pose
        const CPose& GetPose() const;

        // Obtain the collision radius of the robot
        float GetRadius() const;

        virtual void Update( float aDt ) = 0;
    
        // Draw the robot itself, the orientation pointer 
        // and the historical trajectory on the screen
        void Draw( CRender& aRender ) const;


    protected:
        // The function of movement control
        void Move( float aDt );

        // Current pose of the robot
        CPose mPose{ {0.0f, 0.0f}, 0.0f };

        // The radius of the robot
        const float mRadius{ 15.0f };

        // The distance between the left and right wheels
        const float mWheelBase{ 20.0f };    

        // Control the wheels independently
        CWheel mWheels[ 2 ];

        // Record the moving trail
        CTrail mTrail;
};

#endif 