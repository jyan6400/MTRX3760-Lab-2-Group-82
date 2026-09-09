#ifndef CMAP_H
#define CMAP_H

#include "CLoopReader.h"
#include "CRender.h"

#include <string>
#include <vector>

// CMap owns the room geometry loaded from a loop file. It provides wall
// drawing, collision queries and ray-to-wall distance queries.
class CMap
{
    public:
        // Loads a loop file and converts its vertices into wall segments.
        bool Load( const std::string& aFilename );

        // Returns the robot starting pose supplied by the map.
        const CPose& GetStartPose() const;

        // Returns true when a circular robot overlaps any wall.
        bool CheckCollision(
            const Vec2D& aPosition,
            float aRadius ) const;

        // Returns the distance along a ray to the first wall it intersects.
        float GetRayIntersection(
            const Vec2D& aStartPosition,
            float aRayAngle ) const;

        // Draws all wall segments.
        void Draw( CRender& aRender ) const;

    private:
        // A wall is represented by its two endpoints.
        struct Wall
        {
            Vec2D mStart;
            Vec2D mEnd;
        };

        // Builds the closed wall loop from the map vertices.
        void BuildWalls();

        // Returns the shortest distance from a point to a wall segment.
        float PointToSegmentDistance(
            const Vec2D& aPoint,
            const Vec2D& aStart,
            const Vec2D& aEnd ) const;

        CLoopReader mLoopReader;

        std::vector<Wall> mWalls;

        const float mMaxRange{ 2000.0f };
        const float mParallelTolerance{ 0.000001f };
        const float mWallThickness{ 2.0f };
};

#endif