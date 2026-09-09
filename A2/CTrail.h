/*
 * CTrail.h
 *
 * This file declares CTrail, which stores robot positions accumulated during
 * the simulation and renders them as a permanent trajectory.
 */

#ifndef CTRAIL_H
#define CTRAIL_H

#include "CRender.h"

#include <vector>

//-----------------------------------------------------------------------------
// CTrail
//
// CTrail owns the sequence of positions previously occupied by one robot.
// Points remain stored for the complete run so the robot's full trajectory
// remains visible.
//-----------------------------------------------------------------------------
class CTrail
{
    public:

        // Appends one new robot position to the permanent trajectory.
        void AddPoint( const Vec2D& aPosition );

        // Draws line segments between consecutive stored positions.
        void Draw( CRender& aRender ) const;

    private:

        // Ordered sequence of robot positions recorded during the run.
        std::vector<Vec2D> mPoints;

        // Rendered thickness of the trajectory.
        const float mThickness{ 1.0f };
};

#endif