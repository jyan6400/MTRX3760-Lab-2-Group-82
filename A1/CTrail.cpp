#include "CTrail.hpp"

void CTrail::AddPoint( const Vec2D& aPosition )
{
    mPoints.push_back( aPosition );
}

void CTrail::Draw( CRender& aRender ) const
{
    const float Thickness = 1.0f;
    
    // We can't draw line segement with points that less than 2
    if ( mPoints.size() < 2 )
    {
        return;
    }

    // Connect the adjacent points to draw the trail
    for( size_t i = 0; i < mPoints.size() - 1; ++i )
    {
       aRender.DrawLine( mPoints[ i ], mPoints[ i + 1 ], Thickness, GRAY );
    }
}