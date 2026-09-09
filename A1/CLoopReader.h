#ifndef CLOOPREADER_H
#define CLOOPREADER_H

#include "CRender.h"

#include <string>
#include <vector>

// A pose consists of a two-dimensional position and a heading in radians.
struct CPose
{
    Vec2D mPosition;
    float mHeading;
};

// CLoopReader reads one closed loop from a .map file and stores its name,
// starting pose and vertices.
class CLoopReader
{
    public:
        CLoopReader();

        // Loads and parses one loop file.
        bool ReadFile( const std::string& arFilename );

        const std::string& GetName() const;
        const CPose& GetStartPose() const;
        const std::vector<Vec2D>& GetVertices() const;

    private:
        std::string mName;
        CPose mStartPose;
        std::vector<Vec2D> mVertices;

        // Converts headings supplied in degrees to radians.
        const float mDegreesToRadians{ 0.01745329252f };
};

#endif