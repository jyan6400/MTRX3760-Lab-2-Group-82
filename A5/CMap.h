#ifndef CMAP_H
#define CMAP_H

#include "CLoopReader.h"
#include "CRender.h"

#include <string>
#include <vector>

// CMap owns closed-loop geometry loaded from a map file. Its segments can
// represent either room walls or a floor line, and it provides geometric
// queries used by both robot types.
class CMap
{
    public:
        // Loads a loop file and converts its vertices into connected segments.
        bool Load( const std::string& aFilename );

        // Returns the starting pose stored in the map file.
        const CPose& GetStartPose() const;

        // Returns true when a circular robot overlaps any map segment.
        bool CheckCollision(
            const Vec2D& aPosition,
            float aRadius ) const;

        // Returns the distance from a ray origin to the first segment hit.
        float GetRayIntersection(
            const Vec2D& aStartPosition,
            float aRayAngle ) const;

        // Returns true when the supplied point lies on the 5-unit-wide line.
        bool IsPointOnLine(
            const Vec2D& aPoint ) const;

        // Draws the loop using the requested colour and thickness.
        void Draw(
            CRender& aRender,
            CRender::EColour aColour,
            float aThickness ) const;

    private:
        // One straight segment of the closed loop.
        struct Segment
        {
            Vec2D mStart;
            Vec2D mEnd;
        };

        // Constructs a closed set of segments from the loaded vertices.
        void BuildSegments();

        // Returns the shortest distance from a point to a finite segment.
        float PointToSegmentDistance(
            const Vec2D& aPoint,
            const Vec2D& aStart,
            const Vec2D& aEnd ) const;

        CLoopReader mLoopReader;

        std::vector<Segment> mSegments;

        const float mMaxRange{ 2000.0f };
        const float mParallelTolerance{ 0.000001f };

        // The assignment specifies a line width of exactly 5 units.
        const float mLineHalfWidth{ 2.5f };
};

#endif