#ifndef CTRAIL_H
#define CTRAIL_H

#include "CRender.h"

#include <vector>

// CTrail stores every recorded robot position and draws a permanent trajectory
// by connecting neighbouring points with line segments.
class CTrail
{
    public:
        // Adds one robot position to the stored trajectory.
        void AddPoint( const Vec2D& aPosition );

        // Draws all recorded trajectory segments.
        void Draw( CRender& aRender ) const;

    private:
        std::vector<Vec2D> mPoints;

        const float mThickness{ 1.0f };
};

#endif