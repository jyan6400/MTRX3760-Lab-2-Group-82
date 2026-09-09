/*
 * CLoopReader.h
 *
 * This file declares the simple map-file reader used by the simulator. It
 * parses one named closed loop consisting of a starting pose and ordered
 * vertices.
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
// starting pose and ordered vertices. It is responsible only for parsing;
// CMap is responsible for interpreting the vertices as room geometry.
//-----------------------------------------------------------------------------
class CLoopReader
{
    public:

        // Constructs an empty loop reader with a default zero starting pose.
        CLoopReader();

        // Reads and validates one loop description from arFilename.
        // Returns false if the file cannot be opened or contains invalid data.
        bool ReadFile( const std::string& arFilename );

        // Returns the name supplied by the map's loop declaration.
        const std::string& GetName() const;

        // Returns the parsed starting pose with heading stored in radians.
        const CPose& GetStartPose() const;

        // Returns the ordered vertices defining the closed loop.
        const std::vector<Vec2D>& GetVertices() const;

    private:

        // Name of the loop being described.
        std::string mName;

        // Starting pose specified by the map.
        CPose mStartPose;

        // Ordered vertices defining the loop.
        std::vector<Vec2D> mVertices;

        // Map headings are supplied in degrees while simulator trigonometric
        // calculations use radians.
        const float mDegreesToRadians{ 0.01745329252f };
};

#endif