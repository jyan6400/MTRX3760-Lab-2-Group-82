/*
 * CMap.h
 *
 * This file declares CMap, which represents closed segment geometry loaded
 * from a loop file. The same map abstraction supports both the wall boundary
 * and the five-unit-wide floor line.
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
// CMap converts parsed map vertices into generic finite line segments. It
// provides collision, ray-intersection and floor-line queries needed by the
// wall and line followers.
//-----------------------------------------------------------------------------
class CMap
{
    public:

        // Loads a loop map and constructs its closed segment geometry.
        bool Load( const std::string& aFilename );

        // Returns the nominal starting pose defined by the map.
        const CPose& GetStartPose() const;

        // Returns true when a circular robot overlaps a map segment.
        bool CheckCollision(
            const Vec2D& aPosition,
            float aRadius ) const;

        // Returns the distance to the nearest valid forward ray intersection.
        float GetRayIntersection(
            const Vec2D& aStartPosition,
            float aRayAngle ) const;

        // Returns true when aPoint lies within the five-unit-wide floor line.
        bool IsPointOnLine(
            const Vec2D& aPoint ) const;

        // Draws every map segment using the supplied colour and thickness.
        void Draw(
            CRender& aRender,
            CRender::EColour aColour,
            float aThickness ) const;

    private:

        // Generic finite segment representation used for both map types.
        struct Segment
        {
            Vec2D mStart;
            Vec2D mEnd;
        };

        // Converts ordered vertices into a closed sequence of segments.
        void BuildSegments();

        // Returns the shortest distance between a point and a finite segment.
        float PointToSegmentDistance(
            const Vec2D& aPoint,
            const Vec2D& aStart,
            const Vec2D& aEnd ) const;

        CLoopReader mLoopReader;

        std::vector<Segment> mSegments;

        // Half the required five-unit floor-line width.
        const float mLineHalfWidth{ 2.5f };

        // Returned when no nearer range-sensor intersection is present.
        const float mMaxRange{ 2000.0f };

        // Tolerance used when testing whether a ray and segment are parallel.
        const float mParallelTolerance{ 0.000001f };
};

#endif