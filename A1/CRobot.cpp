#include <cmath>
#include "CRobot.hpp"

void CRobot::SetPose( const CPose& aPose )
{
    mPose = aPose;
}

const CPose& CRobot::GetPose() const
{
    return mPose;
}

float CRobot::GetRadius() const
{
    return mRadius;
}

void CRobot::Move( float aDt )
{
    // Read the current speed
    float LeftSpeed  = mWheels[0].GetSpeed();
    float RightSpeed = mWheels[1].GetSpeed();

    float LinearVelocity  = ( LeftSpeed + RightSpeed ) / 2.0f;
    float AngularVelocity = ( RightSpeed - LeftSpeed ) / mWheelBase;

    // Update the heading angle
    mPose.mHeading += AngularVelocity * aDt;

    // Update the coordinate according to the new direction
    mPose.mPosition.x += LinearVelocity * std::cos( mPose.mHeading ) * aDt;
    mPose.mPosition.y += LinearVelocity * std::sin( mPose.mHeading ) * aDt;

    // Record the latest position to the Trail list
    mTrail.AddPoint( mPose.mPosition );
}

void CRobot::Draw( CRender& aRender ) const
{
    const float HeadingLineLength = mRadius;
    const float HeadingLineThickness = 2.0f;

    // Draw the 
    mTrail.Draw( aRender );

    aRender.DrawCircle( mPose.mPosition, (int)mRadius, BLUE );

    // Calculate and draw the heading
    Vec2D HeadingEnd
    {
        mPose.mPosition.x + HeadingLineLength * std::cos( mPose.mHeading ),
        mPose.mPosition.y + HeadingLineLength * std::sin( mPose.mHeading )
    };
    aRender.DrawLine( mPose.mPosition, HeadingEnd, HeadingLineThickness, WHITE );
}