/*
 * CRobot.cpp
 *
 * This file implements the common robot pose, wheel command,
 * differential-drive movement and rendering behaviour inherited by both A2
 * robot types.
 */

#include "CRobot.h"

#include <cmath>

//-----------------------------------------------------------------------------
void CRobot::SetPose( const CPose& aPose )
{
    mPose =
        aPose;
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

    // Average wheel speed controls translation, while their difference
    // controls rotation for the differential-drive model.
    float LinearVelocity =
        ( LeftSpeed + RightSpeed ) / 2.0f;

    float AngularVelocity =
        ( RightSpeed - LeftSpeed ) / mWheelBase;

    mPose.mHeading +=
        AngularVelocity * aDt;

    mPose.mPosition.x +=
        LinearVelocity
        * std::cos( mPose.mHeading )
        * aDt;

    mPose.mPosition.y +=
        LinearVelocity
        * std::sin( mPose.mHeading )
        * aDt;

    // Each movement update contributes another point to the permanent trail.
    mTrail.AddPoint(
        mPose.mPosition );
}

//-----------------------------------------------------------------------------
void CRobot::Draw( CRender& aRender ) const
{
    // Draw the trail first so the current robot remains visible above it.
    mTrail.Draw(
        aRender );

    aRender.DrawCircle(
        mPose.mPosition,
        (int)mRadius,
        CRender::COLOUR_BLUE );

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