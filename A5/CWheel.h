/*
 * CWheel.h
 *
 * This file declares CWheel, which represents one independently controlled
 * wheel used by a simulated robot.
 */

#ifndef CWHEEL_H
#define CWHEEL_H

//-----------------------------------------------------------------------------
// CWheel
//
// CWheel stores the commanded speed of one wheel. CRobot owns two CWheel
// objects and uses their speeds when calculating differential-drive motion.
//-----------------------------------------------------------------------------
class CWheel
{
    public:

        // Sets the current commanded speed of this wheel.
        void SetSpeed( float aSpeed );

        // Returns the current commanded speed of this wheel.
        float GetSpeed() const;

    private:

        // Current commanded wheel speed.
        float mSpeed{ 0.0f };
};

#endif