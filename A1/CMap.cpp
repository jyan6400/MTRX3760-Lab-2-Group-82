/*
 * CMap.cpp
 *
 * This file implements map loading, wall construction, point-to-segment
 * distance calculations, collision detection, sensor ray intersection and
 * room rendering for CMap.
 */

#include "CMap.h"

#include <cmath>

//-----------------------------------------------------------------------------
bool CMap::Load( const std::string& aFilename )
{
    bool Okay =
        mLoopReader.ReadFile(
            aFilename );

    // Do not construct geometry from an invalid map.
    if( Okay )
    {
        BuildWalls();
    }

    return Okay;
}

//-----------------------------------------------------------------------------
void CMap::BuildWalls()
{
    mWalls.clear();

    const std::vector<Vec2D>& Vertices =
        mLoopReader.GetVertices();

    if( !Vertices.empty() )
    {
        // Beginning with the final vertex automatically creates the closing
        // segment between the final and first vertices.
        Vec2D Previous =
            Vertices.back();

        for( const Vec2D& Vertex : Vertices )
        {
            mWalls.push_back(
                { Previous, Vertex } );

            Previous =
                Vertex;
        }
    }
}

//-----------------------------------------------------------------------------
const CPose& CMap::GetStartPose() const
{
    return mLoopReader.GetStartPose();
}

//-----------------------------------------------------------------------------
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
        // Project the point onto the infinite line containing the segment.
        T =
            ( ( aPoint.x - aStart.x ) * Dx
            + ( aPoint.y - aStart.y ) * Dy )
            / LengthSquare;

        // Clamp the projection so the closest point remains on the finite
        // segment rather than extending beyond either endpoint.
        if( T < 0.0f )
        {
            T = 0.0f;
        }

        if( T > 1.0f )
        {
            T = 1.0f;
        }
    }

    Vec2D ClosestPoint
    {
        aStart.x + T * Dx,
        aStart.y + T * Dy
    };

    float PointDx =
        aPoint.x - ClosestPoint.x;

    float PointDy =
        aPoint.y - ClosestPoint.y;

    float Distance =
        std::sqrt(
            PointDx * PointDx
            + PointDy * PointDy );

    return Distance;
}

//-----------------------------------------------------------------------------
bool CMap::CheckCollision(
    const Vec2D& aPosition,
    float aRadius ) const
{
    bool Collided =
        false;

    // A circular robot overlaps a wall whenever the shortest distance from its
    // centre to that segment becomes smaller than the robot radius.
    for( const Wall& W : mWalls )
    {
        if( PointToSegmentDistance(
                aPosition,
                W.mStart,
                W.mEnd ) < aRadius )
        {
            Collided =
                true;
        }
    }

    return Collided;
}

//-----------------------------------------------------------------------------
float CMap::GetRayIntersection(
    const Vec2D& aStartPosition,
    float aRayAngle ) const
{
    float ClosestDistance =
        mMaxRange;

    // Unit direction vector for the sensor ray.
    Vec2D Direction
    {
        std::cos( aRayAngle ),
        std::sin( aRayAngle )
    };

    for( const Wall& W : mWalls )
    {
        float SegmentX =
            W.mEnd.x - W.mStart.x;

        float SegmentY =
            W.mEnd.y - W.mStart.y;

        // A near-zero cross-product denominator means the sensor ray and wall
        // are parallel and therefore do not have a unique intersection.
        float Denominator =
            Direction.x * SegmentY
            - Direction.y * SegmentX;

        if( std::fabs( Denominator ) > mParallelTolerance )
        {
            float OffsetX =
                W.mStart.x
                - aStartPosition.x;

            float OffsetY =
                W.mStart.y
                - aStartPosition.y;

            // T specifies distance forward along the sensor ray.
            float T =
                ( OffsetX * SegmentY
                - OffsetY * SegmentX )
                / Denominator;

            // U specifies the intersection location along the finite wall.
            // Values in [0,1] lie between the two wall endpoints.
            float U =
                ( OffsetX * Direction.y
                - OffsetY * Direction.x )
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

//-----------------------------------------------------------------------------
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