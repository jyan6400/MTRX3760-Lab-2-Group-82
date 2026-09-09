#include "CRobot.h"

#include <cmath>
#include <cstdlib>

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

void CRobot::EnableMovementNoise(
    float aNoiseFraction )
{
    if( aNoiseFraction >= 0.0f )
    {
        mMovementNoiseFraction =
            aNoiseFraction;

        mMovementNoiseEnabled =
            true;
    }
}

float CRobot::RandomOffset(
    float aMagnitude ) const
{
    float UnitRandom =
        float( std::rand() )
        / float( RAND_MAX );

    float Offset =
        ( 2.0f * UnitRandom - 1.0f )
        * aMagnitude;

    return Offset;
}

void CRobot::SetWheelSpeeds(
    float aLeftSpeed,
    float aRightSpeed )
{
    mWheels[WHEEL_LEFT].SetSpeed(
        aLeftSpeed );

    mWheels[WHEEL_RIGHT].SetSpeed(
        aRightSpeed );
}

void CRobot::Move( float aDt )
{
    // Calculate how far each wheel would travel during this timestep.
    float LeftDistance =
        mWheels[WHEEL_LEFT].GetSpeed()
        * aDt;

    float RightDistance =
        mWheels[WHEEL_RIGHT].GetSpeed()
        * aDt;

    // A5 adds an independent random perturbation to the distance travelled
    // by each wheel during every simulation update.
    if( mMovementNoiseEnabled )
    {
        LeftDistance *=
            1.0f
            + RandomOffset(
                mMovementNoiseFraction );

        RightDistance *=
            1.0f
            + RandomOffset(
                mMovementNoiseFraction );
    }

    float LinearDistance =
        ( LeftDistance + RightDistance )
        / 2.0f;

    float HeadingChange =
        ( RightDistance - LeftDistance )
        / mWheelBase;

    mPose.mHeading +=
        HeadingChange;

    mPose.mPosition.x +=
        LinearDistance
        * std::cos( mPose.mHeading );

    mPose.mPosition.y +=
        LinearDistance
        * std::sin( mPose.mHeading );

    mTrail.AddPoint(
        mPose.mPosition );
}

void CRobot::Draw(
    CRender& aRender ) const
{
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