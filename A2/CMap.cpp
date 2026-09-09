#include "CMap.h"

#include <cmath>

bool CMap::Load( const std::string& aFilename )
{
    bool Okay =
        mLoopReader.ReadFile( aFilename );

    if( Okay )
    {
        BuildSegments();
    }

    return Okay;
}

void CMap::BuildSegments()
{
    mSegments.clear();

    const std::vector<Vec2D>& Vertices =
        mLoopReader.GetVertices();

    if( !Vertices.empty() )
    {
        Vec2D Previous =
            Vertices.back();

        for( const Vec2D& Vertex : Vertices )
        {
            mSegments.push_back(
                { Previous, Vertex } );

            Previous =
                Vertex;
        }
    }
}

const CPose& CMap::GetStartPose() const
{
    return mLoopReader.GetStartPose();
}

float CMap::PointToSegmentDistance(
    const Vec2D& aPoint,
    const Vec2D& aStart,
    const Vec2D& aEnd ) const
{
    float Dx =
        aEnd.x - aStart.x;

    float Dy =
        aEnd.y - aStart.y;

    float LengthSquare =
        Dx * Dx + Dy * Dy;

    float T =
        0.0f;

    if( LengthSquare > 0.0f )
    {
        T =
            ( ( aPoint.x - aStart.x ) * Dx
            + ( aPoint.y - aStart.y ) * Dy )
            / LengthSquare;

        if( T < 0.0f )
        {
            T = 0.0f;
        }

        if( T > 1.0f )
        {
            T = 1.0f;
        }
    }

    float ClosestX =
        aStart.x + T * Dx;

    float ClosestY =
        aStart.y + T * Dy;

    float Ddx =
        aPoint.x - ClosestX;

    float Ddy =
        aPoint.y - ClosestY;

    float Distance =
        std::sqrt(
            Ddx * Ddx
            + Ddy * Ddy );

    return Distance;
}

bool CMap::CheckCollision(
    const Vec2D& aPosition,
    float aRadius ) const
{
    bool Collided =
        false;

    for( const Segment& S : mSegments )
    {
        if( PointToSegmentDistance(
                aPosition,
                S.mStart,
                S.mEnd ) < aRadius )
        {
            Collided =
                true;
        }
    }

    return Collided;
}

float CMap::GetRayIntersection(
    const Vec2D& aStartPosition,
    float aRayAngle ) const
{
    float ClosestDistance =
        mMaxRange;

    Vec2D Direction
    {
        std::cos( aRayAngle ),
        std::sin( aRayAngle )
    };

    for( const Segment& S : mSegments )
    {
        float Sx =
            S.mEnd.x - S.mStart.x;

        float Sy =
            S.mEnd.y - S.mStart.y;

        float Denominator =
            Direction.x * Sy
            - Direction.y * Sx;

        if( std::fabs( Denominator ) > mParallelTolerance )
        {
            float Ex =
                S.mStart.x
                - aStartPosition.x;

            float Ey =
                S.mStart.y
                - aStartPosition.y;

            // T is distance along the ray.
            float T =
                ( Ex * Sy
                - Ey * Sx )
                / Denominator;

            // U identifies the position along the finite map segment.
            float U =
                ( Ex * Direction.y
                - Ey * Direction.x )
                / Denominator;

            if( T >= 0.0f
                && U >= 0.0f
                && U <= 1.0f
                && T < ClosestDistance )
            {
                ClosestDistance =
                    T;
            }
        }
    }

    return ClosestDistance;
}

bool CMap::IsPointOnLine(
    const Vec2D& aPoint ) const
{
    bool OnLine =
        false;

    for( const Segment& S : mSegments )
    {
        float Distance =
            PointToSegmentDistance(
                aPoint,
                S.mStart,
                S.mEnd );

        if( Distance <= mLineHalfWidth )
        {
            OnLine =
                true;
        }
    }

    return OnLine;
}

void CMap::Draw(
    CRender& aRender,
    CRender::EColour aColour,
    float aThickness ) const
{
    for( const Segment& S : mSegments )
    {
        aRender.DrawLine(
            S.mStart,
            S.mEnd,
            aThickness,
            aColour );
    }
}