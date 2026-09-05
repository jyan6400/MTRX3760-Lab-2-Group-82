// CWallFollower is the class enable the robot to move along the right wall
// Use the proportional control algorithm to adjust the differential speed of 
// the left and right wheels, achieving navigation along the wall and obstacle 
// avoidance at corners.
#ifndef CWALLFOLLOWER_HPP
#define CWALLFOLLOWER_HPP

#include "CRobot.hpp"
#include "CRangeSensor.hpp"

class CMap;

class CWallFollower : public CRobot
{
    public:
        // Requires reference to the map to provide
        // sensor detection and collision checks
        CWallFollower( const CMap& aMap );

        // Control steering, update physical movement and detect collisions
        void Update( float aDt );

        // Obtain the total number of collisions that occurred
        int GetCollisionCount() const;

    private:
        // Calculate the speed difference between the left 
        // and right wheels based on the sensor readings
        void Steer();
        
        // Check if the current position collides with the wall
        void CheckCollision();

        const CMap& mMap;

        // Two range sensors
        CRangeSensor mSensors[ 2 ];  

        // Basic forward speed
        const float mBaseSpeed{ 80.0f };

        // Desired distance from the right wall
        const float mTargetWallDistance{ 60.0f };
        
        // The ratio coefficient of the distance from the right wall
        const float mKp{ 0.6f };
        
        // The control gain coefficient for the sharp turn
        const float mKTurn{ 0.8f };
        
        // The distance threshold for triggering deceleration/ turning
        const float mFrontThreshold{ 80.0f };

        // Collision counter
        int mCollisionCount{ 0 };


};

#endif