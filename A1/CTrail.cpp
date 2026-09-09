#include "CTrail.h"

void CTrail::AddPoint( const Vec2D& aPosition )
{
    mPoints.push_back( aPosition );
}

void CTrail::Draw( CRender& aRender ) const
{
    if( mPoints.size() >= 2 )
    {
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