/*
 * CLoopReader.h
 *
 * This file declares the map-file reader used by the A5 simulator. It parses
 * one named closed loop consisting of a starting pose and ordered vertices.
 */

#ifndef CLOOPREADER_H
#define CLOOPREADER_H

#include "CRender.h"

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// CPose
//
// CPose groups a two-dimensional world position with a heading stored in
// radians.
//-----------------------------------------------------------------------------
struct CPose
{
    Vec2D mPosition;
    float mHeading;
};

//-----------------------------------------------------------------------------
// CLoopReader
//
// CLoopReader parses the supplied loop-map format and stores its loop name,
// starting pose and ordered vertices. CMap interprets the vertices as
// simulation geometry.
//-----------------------------------------------------------------------------
class CLoopReader
{
    public:

        // Constructs an empty reader with a zero starting pose.
        CLoopReader();

        // Reads and validates one loop description from arFilename.
        bool ReadFile( const std::string& arFilename );

        // Returns the parsed loop name.
        const std::string& GetName() const;

        // Returns the starting pose with heading stored in radians.
        const CPose& GetStartPose() const;

        // Returns the ordered vertices defining the closed loop.
        const std::vector<Vec2D>& GetVertices() const;

    private:

        std::string mName;

        CPose mStartPose;

        std::vector<Vec2D> mVertices;

        // Input map headings are given in degrees while simulation calculations
        // consistently use radians.
        const float mDegreesToRadians{ 0.01745329252f };
};

#endif