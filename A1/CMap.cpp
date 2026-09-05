#include "CMap.hpp"
#include <cmath>

bool CMap::Load( const std::string& aFilename )
{
    bool Okay = mLoopReader.ReadFile( aFilename );
    if( Okay )
    {
        BuildWalls();
    }
    return Okay;
}

void CMap::BuildWalls()
{
    mWalls.clear();

    const std::vector<Vec2D>& Vertices = mLoopReader.GetVertices();
    if( !Vertices.empty() )
    {
        Vec2D Previous = Vertices.back();
        for( const Vec2D& Vertex : Vertices )
        {
            mWalls.push_back( { Previous, Vertex } );
            Previous = Vertex;
        }
    }
}

const CPose& CMap::GetStartPose() const
{
    return mLoopReader.GetStartPose();
}

// Support function: Calculates the shortest distance from a two-dimensional point to a line segment.
static float PointToSegmentDistance( const Vec2D& aPoint, const Vec2D& aStart, const Vec2D& aEnd )
{
    float Dx = aEnd.x - aStart.x;
    float Dy = aEnd.y - aStart.y;
    float LengthSquare = Dx * Dx + Dy * Dy;

    float T = 0.0f;
    if( LengthSquare > 0.0f )
    {
        T = ( (aPoint.x - aStart.x) * Dx + (aPoint.y - aStart.y) * Dy ) / LengthSquare;
        if( T < 0.0f ) { T = 0.0f; }
        if( T > 1.0f ) { T = 1.0f; }
    }

    float ClosestX = aStart.x + T * Dx;
    float ClosestY = aStart.y + T * Dy;

    float Ddx = aPoint.x - ClosestX;
    float Ddy = aPoint.y - ClosestY;

    float Distance = std::sqrt( Ddx * Ddx + Ddy * Ddy );

    return Distance;
}

bool CMap::CheckCollision( const Vec2D& aPosition, float aRadius ) const
{
    bool Collided = false;

    for( const Wall& W : mWalls )
    {
        if( PointToSegmentDistance( aPosition, W.mStart, W.mEnd ) < aRadius )
        {
            Collided = true;
        }
    }

    return Collided;
}

float CMap::GetRayIntersection( const Vec2D& aStartPosition, float aRayAngle ) const
{
    float ClosestDistance = mMaxRange;

    Vec2D Direction{ std::cos( aRayAngle ), std::sin( aRayAngle ) };

    for( const Wall& W : mWalls )
    {
        float Sx = W.mEnd.x - W.mStart.x;
        float Sy = W.mEnd.y - W.mStart.y;

        // 
        float Denominator = Direction.x * Sy - Direction.y * Sx;

        // The condition of rays parallel to the wall
        if( std::fabs( Denominator ) > 1e-6f )
        {
            float Ex = W.mStart.x - aStartPosition.x;
            float Ey = W.mStart.y - aStartPosition.y;

            // T represents the distance along the ray
            float T = ( Ex * Sy - Ey * Sx ) / Denominator;                    
            
            // U represents the position parameter on the wall segment
            float U = ( Ex * Direction.y - Ey * Direction.x ) / Denominator;  

            // Make sure the ray intersects within the wall segment in the forward direction.
            if( T >= 0.0f && U >= 0.0f && U <= 1.0f && T < ClosestDistance )
            {
                ClosestDistance = T;
            }
        }
    }

    return ClosestDistance;
}

void CMap::Draw( CRender& arRender ) const
{
    const float WallThickness = 2.0f;

    for( const Wall& W : mWalls )
    {
        arRender.DrawLine( W.mStart, W.mEnd, WallThickness, RAYWHITE );
    }
}
