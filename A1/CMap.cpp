#include "CMap.h"

#include <cmath>

bool CMap::Load( const std::string& aFilename )
{
    bool Okay =
        mLoopReader.ReadFile( aFilename );

    if( Okay )
    {
        BuildWalls();
    }

    return Okay;
}

void CMap::BuildWalls()
{
    mWalls.clear();

    const std::vector<Vec2D>& Vertices =
        mLoopReader.GetVertices();

    if( !Vertices.empty() )
    {
        Vec2D Previous =
            Vertices.back();

        for( const Vec2D& Vertex : Vertices )
        {
            mWalls.push_back(
                { Previous, Vertex } );

            Previous = Vertex;
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

    float T = 0.0f;

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

    return std::sqrt(
        Ddx * Ddx + Ddy * Ddy );
}

bool CMap::CheckCollision(
    const Vec2D& aPosition,
    float aRadius ) const
{
    bool Collided = false;

    for( const Wall& W : mWalls )
    {
        if( PointToSegmentDistance(
                aPosition,
                W.mStart,
                W.mEnd ) < aRadius )
        {
            Collided = true;
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

    for( const Wall& W : mWalls )
    {
        float Sx =
            W.mEnd.x - W.mStart.x;

        float Sy =
            W.mEnd.y - W.mStart.y;

        float Denominator =
            Direction.x * Sy
            - Direction.y * Sx;

        // Parallel or almost-parallel rays do not produce a useful
        // intersection with this wall segment.
        if( std::fabs( Denominator ) > mParallelTolerance )
        {
            float Ex =
                W.mStart.x - aStartPosition.x;

            float Ey =
                W.mStart.y - aStartPosition.y;

            // T is the distance along the ray.
            float T =
                ( Ex * Sy - Ey * Sx )
                / Denominator;

            // U is the position along the finite wall segment.
            float U =
                ( Ex * Direction.y
                - Ey * Direction.x )
                / Denominator;

            if( T >= 0.0f
                && U >= 0.0f
                && U <= 1.0f
                && T < ClosestDistance )
            {
                ClosestDistance = T;
            }
        }
    }

    return ClosestDistance;
}

void CMap::Draw( CRender& aRender ) const
{
    for( const Wall& W : mWalls )
    {
        aRender.DrawLine(
            W.mStart,
            W.mEnd,
            mWallThickness,
            CRender::COLOUR_WHITE );
    }
}