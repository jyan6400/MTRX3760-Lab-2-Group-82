/*
 * CMap.h
 *
 * This file declares CMap, which owns the room geometry loaded from a map file
 * and provides wall drawing, circular collision detection and range-sensor
 * ray-intersection queries.
 */

#ifndef CMAP_H
#define CMAP_H

#include "CLoopReader.h"
#include "CRender.h"

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// CMap
//
// CMap represents the room used by the wall-following simulation. It owns a
// CLoopReader and converts the loaded vertices into a closed collection of
// straight wall segments. Other objects query the map through its interface
// rather than manipulating its geometry directly.
//-----------------------------------------------------------------------------
class CMap
{
    public:

        // Loads a loop map from aFilename and constructs its wall segments.
        // Returns true when the map file is parsed successfully.
        bool Load( const std::string& aFilename );

        // Returns the starting pose specified by the loaded map.
        const CPose& GetStartPose() const;

        // Returns true when a circular robot overlaps at least one wall.
        bool CheckCollision(
            const Vec2D& aPosition,
            float aRadius ) const;

        // Casts a ray from aStartPosition at aRayAngle and returns the distance
        // to the nearest forward wall intersection.
        float GetRayIntersection(
            const Vec2D& aStartPosition,
            float aRayAngle ) const;

        // Draws every wall segment in the room.
        void Draw( CRender& aRender ) const;

    private:

        // Represents one finite straight wall segment.
        struct Wall
        {
            Vec2D mStart;
            Vec2D mEnd;
        };

        // Converts the ordered map vertices into a closed set of wall segments.
        void BuildWalls();

        // Returns the shortest distance between a point and a finite segment.
        // This is used for circular robot collision detection.
        float PointToSegmentDistance(
            const Vec2D& aPoint,
            const Vec2D& aStart,
            const Vec2D& aEnd ) const;

        // Parser owned by the map.
        CLoopReader mLoopReader;

        // Closed collection of room walls.
        std::vector<Wall> mWalls;

        // Distance returned when no nearer ray intersection is found.
        const float mMaxRange{ 2000.0f };

        // Tolerance used to treat almost-parallel lines as parallel.
        const float mParallelTolerance{ 0.000001f };

        // Visual thickness of wall segments.
        const float mWallThickness{ 2.0f };
};

#endif