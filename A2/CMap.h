/*
 * CMap.h
 *
 * This file declares CMap, which represents closed segment geometry loaded
 * from a loop file. The same abstraction supports both the A2 wall boundary
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
// CMap owns one parsed loop and converts its vertices into generic finite line
// segments. It provides geometric queries needed by both robot types: circular
// collision detection, ray intersection and detection of whether a point lies
// over the five-unit-wide floor line.
//-----------------------------------------------------------------------------
class CMap
{
    public:

        // Loads a loop map from aFilename and constructs the closed segment
        // geometry. Returns true when parsing succeeds.
        bool Load( const std::string& aFilename );

        // Returns the starting pose defined by this map.
        const CPose& GetStartPose() const;

        // Returns true when a circular robot overlaps any map segment.
        bool CheckCollision(
            const Vec2D& aPosition,
            float aRadius ) const;

        // Returns the distance from a ray origin to the nearest valid forward
        // segment intersection.
        float GetRayIntersection(
            const Vec2D& aStartPosition,
            float aRayAngle ) const;

        // Returns true when aPoint lies within the five-unit-wide line centred
        // on any segment in this map.
        bool IsPointOnLine(
            const Vec2D& aPoint ) const;

        // Draws every map segment using the supplied colour and thickness.
        void Draw(
            CRender& aRender,
            CRender::EColour aColour,
            float aThickness ) const;

    private:

        // Generic representation used for both wall and line geometry.
        struct Segment
        {
            Vec2D mStart;
            Vec2D mEnd;
        };

        // Converts ordered map vertices into a closed set of segments.
        void BuildSegments();

        // Returns the shortest distance between aPoint and a finite segment.
        float PointToSegmentDistance(
            const Vec2D& aPoint,
            const Vec2D& aStart,
            const Vec2D& aEnd ) const;

        // Parser owned by this map.
        CLoopReader mLoopReader;

        // Closed geometry represented as straight finite segments.
        std::vector<Segment> mSegments;

        // Half of the required five-unit line width.
        const float mLineHalfWidth{ 2.5f };

        // Default distance when a sensing ray finds no nearer intersection.
        const float mMaxRange{ 2000.0f };

        // Tolerance used when testing whether lines are effectively parallel.
        const float mParallelTolerance{ 0.000001f };
};

#endif