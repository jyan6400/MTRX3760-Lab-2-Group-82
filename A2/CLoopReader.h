/*
 * CLoopReader.h
 *
 * This file declares the map-file reader used by both A2 maps. It parses one
 * named closed loop consisting of a starting pose and ordered vertices.
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
// CLoopReader parses the supplied loop-map format and stores the loop name,
// starting pose and ordered vertices. CMap is then responsible for interpreting
// those vertices as simulation geometry.
//-----------------------------------------------------------------------------
class CLoopReader
{
    public:

        // Constructs an empty reader with a default zero starting pose.
        CLoopReader();

        // Reads and validates one loop description from arFilename.
        // Returns false when the file cannot be opened or contains invalid
        // input.
        bool ReadFile( const std::string& arFilename );

        // Returns the map's loop name.
        const std::string& GetName() const;

        // Returns the parsed starting pose with heading stored in radians.
        const CPose& GetStartPose() const;

        // Returns the ordered vertices defining the loop.
        const std::vector<Vec2D>& GetVertices() const;

    private:

        std::string mName;

        CPose mStartPose;

        std::vector<Vec2D> mVertices;

        // Input headings are given in degrees while the simulator uses radians.
        const float mDegreesToRadians{ 0.01745329252f };
};

#endif