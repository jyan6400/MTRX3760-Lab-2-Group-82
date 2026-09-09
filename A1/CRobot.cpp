/*
 * CRobot.cpp
 *
 * This file implements the common robot pose, wheel command,
 * differential-drive movement and rendering behaviour used by CRobot
 * subclasses.
 */

#include "CRobot.h"

#include <cmath>

//-----------------------------------------------------------------------------
void CRobot::SetPose( const CPose& aPose )
{
    mPose = aPose;
}

//-----------------------------------------------------------------------------
const CPose& CRobot::GetPose() const
{
    return mPose;
}

//-----------------------------------------------------------------------------
float CRobot::GetRadius() const
{
    return mRadius;
}

//-----------------------------------------------------------------------------
void CRobot::SetWheelSpeeds(
    float aLeftSpeed,
    float aRightSpeed )
{
    mWheels[WHEEL_LEFT].SetSpeed(
        aLeftSpeed );

    mWheels[WHEEL_RIGHT].SetSpeed(
        aRightSpeed );
}

//-----------------------------------------------------------------------------
void CRobot::Move( float aDt )
{
    float LeftSpeed =
        mWheels[WHEEL_LEFT].GetSpeed();

    float RightSpeed =
        mWheels[WHEEL_RIGHT].GetSpeed();

    // For differential-drive motion, average wheel speed determines forward
    // velocity while the wheel-speed difference determines angular velocity.
    float LinearVelocity =
        ( LeftSpeed + RightSpeed ) / 2.0f;

    float AngularVelocity =
        ( RightSpeed - LeftSpeed ) / mWheelBase;

    mPose.mHeading +=
        AngularVelocity * aDt;

    // Advance the robot in the direction of its updated heading.
    mPose.mPosition.x +=
        LinearVelocity
        * std::cos( mPose.mHeading )
        * aDt;

    mPose.mPosition.y +=
        LinearVelocity
        * std::sin( mPose.mHeading )
        * aDt;

    // Every completed movement update is recorded so the trail remains visible
    // for the entire simulation.
    mTrail.AddPoint(
        mPose.mPosition );
}

//-----------------------------------------------------------------------------
void CRobot::Draw( CRender& aRender ) const
{
    // Draw the trail first so the current robot appears above its trajectory.
    mTrail.Draw(
        aRender );

    aRender.DrawCircle(
        mPose.mPosition,
        (int)mRadius,
        CRender::COLOUR_BLUE );

    // The heading indicator extends from the centre to the edge of the body.
    Vec2D HeadingEnd
    {
        mPose.mPosition.x
            + mRadius
            * std::cos( mPose.mHeading ),

        mPose.mPosition.y
            + mRadius
            * std::sin( mPose.mHeading )
    };

    aRender.DrawLine(
        mPose.mPosition,
        HeadingEnd,
        mHeadingLineThickness,
        CRender::COLOUR_WHITE );
}