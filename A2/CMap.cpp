/*
 * CMap.cpp
 *
 * This file implements generic segment construction, collision detection,
 * ray intersection, floor-line sensing and rendering for CMap.
 */

#include "CMap.h"

#include <cmath>

//-----------------------------------------------------------------------------
bool CMap::Load( const std::string& aFilename )
{
    bool Okay =
        mLoopReader.ReadFile(
            aFilename );

    if( Okay )
    {
        BuildSegments();
    }

    return Okay;
}

//-----------------------------------------------------------------------------
void CMap::BuildSegments()
{
    mSegments.clear();

    const std::vector<Vec2D>& Vertices =
        mLoopReader.GetVertices();

    if( !Vertices.empty() )
    {
        // Starting with the final vertex automatically closes the loop between
        // the last and first supplied vertices.
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

        // Clamp the projection to the finite segment endpoints.
        if( T < 0.0f )
        {
            T =
                0.0f;
        }

        if( T > 1.0f )
        {
            T =
                1.0f;
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

    for( const Segment& CurrentSegment : mSegments )
    {
        if( PointToSegmentDistance(
                aPosition,
                CurrentSegment.mStart,
                CurrentSegment.mEnd ) < aRadius )
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

    Vec2D Direction
    {
        std::cos( aRayAngle ),
        std::sin( aRayAngle )
    };

    for( const Segment& CurrentSegment : mSegments )
    {
        float SegmentX =
            CurrentSegment.mEnd.x
            - CurrentSegment.mStart.x;

        float SegmentY =
            CurrentSegment.mEnd.y
            - CurrentSegment.mStart.y;

        // A near-zero cross product means the ray and segment are parallel.
        float Denominator =
            Direction.x * SegmentY
            - Direction.y * SegmentX;

        if( std::fabs( Denominator ) > mParallelTolerance )
        {
            float OffsetX =
                CurrentSegment.mStart.x
                - aStartPosition.x;

            float OffsetY =
                CurrentSegment.mStart.y
                - aStartPosition.y;

            // T gives distance forward along the ray.
            float T =
                ( OffsetX * SegmentY
                - OffsetY * SegmentX )
                / Denominator;

            // U gives the position along the finite segment. Only values from
            // zero to one lie between the two segment endpoints.
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
bool CMap::IsPointOnLine(
    const Vec2D& aPoint ) const
{
    bool OnLine =
        false;

    // The line is exactly five units wide, so a sensor is on the line whenever
    // its point lies no more than 2.5 units from a centre segment.
    for( const Segment& CurrentSegment : mSegments )
    {
        if( PointToSegmentDistance(
                aPoint,
                CurrentSegment.mStart,
                CurrentSegment.mEnd ) <= mLineHalfWidth )
        {
            OnLine =
                true;
        }
    }

    return OnLine;
}

//-----------------------------------------------------------------------------
void CMap::Draw(
    CRender& aRender,
    CRender::EColour aColour,
    float aThickness ) const
{
    for( const Segment& CurrentSegment : mSegments )
    {
        aRender.DrawLine(
            CurrentSegment.mStart,
            CurrentSegment.mEnd,
            aThickness,
            aColour );
    }
}