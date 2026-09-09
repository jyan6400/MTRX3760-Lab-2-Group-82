/*
 * CTrail.cpp
 *
 * This file implements storage and rendering of the permanent robot
 * trajectory represented by CTrail.
 */

#include "CTrail.h"

//-----------------------------------------------------------------------------
void CTrail::AddPoint( const Vec2D& aPosition )
{
    mPoints.push_back( aPosition );
}

//-----------------------------------------------------------------------------
void CTrail::Draw( CRender& aRender ) const
{
    // At least two recorded positions are required to form a visible segment.
    if( mPoints.size() >= 2 )
    {
        // Consecutive points are joined so the entire recorded trajectory is
        // retained without CTrail needing to know anything about robot motion.
        for( std::size_t i = 0; i < mPoints.size() - 1; ++i )
        {
            aRender.DrawLine(
                mPoints[i],
                mPoints[i + 1],
                mThickness,
                CRender::COLOUR_GREY );
        }
    }
}