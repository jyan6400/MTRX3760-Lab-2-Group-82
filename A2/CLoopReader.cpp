/*
 * CLoopReader.cpp
 *
 * This file implements parsing of the supplied loop-map format. It accepts
 * loop, startpose and vertex entries, ignores comments and blank lines, and
 * reports malformed input to the console.
 */

#include "CLoopReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//-----------------------------------------------------------------------------
CLoopReader::CLoopReader()
    :
        mStartPose(
            { { 0.0f, 0.0f }, 0.0f } )
{
}

//-----------------------------------------------------------------------------
const std::string& CLoopReader::GetName() const
{
    return mName;
}

//-----------------------------------------------------------------------------
const CPose& CLoopReader::GetStartPose() const
{
    return mStartPose;
}

//-----------------------------------------------------------------------------
const std::vector<Vec2D>& CLoopReader::GetVertices() const
{
    return mVertices;
}

//-----------------------------------------------------------------------------
bool CLoopReader::ReadFile(
    const std::string& arFilename )
{
    bool Okay =
        true;

    std::ifstream File(
        arFilename );

    if( !File )
    {
        std::cout
            << "CLoopReader: could not open file '"
            << arFilename
            << "'"
            << std::endl;

        Okay =
            false;
    }

    std::string Line;

    int LineNumber =
        0;

    bool HaveLoop =
        false;

    while( Okay && std::getline( File, Line ) )
    {
        ++LineNumber;

        // Remove everything after '#' so both whole-line and trailing comments
        // are ignored by the parser.
        std::string::size_type Hash =
            Line.find( '#' );

        if( Hash != std::string::npos )
        {
            Line =
                Line.substr(
                    0,
                    Hash );
        }

        std::istringstream Words(
            Line );

        std::string Keyword;

        if( Words >> Keyword )
        {
            if( Keyword == "loop" )
            {
                if( HaveLoop )
                {
                    std::cout
                        << "CLoopReader: a second 'loop' on line "
                        << LineNumber
                        << " (a file describes one loop)"
                        << std::endl;

                    Okay =
                        false;
                }
                else if( !( Words >> mName ) )
                {
                    std::cout
                        << "CLoopReader: 'loop' needs a name on line "
                        << LineNumber
                        << std::endl;

                    Okay =
                        false;
                }
                else
                {
                    HaveLoop =
                        true;
                }
            }
            else if( Keyword == "startpose" )
            {
                float X =
                    0.0f;

                float Y =
                    0.0f;

                float HeadingDegrees =
                    0.0f;

                if( !( Words >> X >> Y >> HeadingDegrees ) )
                {
                    std::cout
                        << "CLoopReader: 'startpose' needs x, y and heading on line "
                        << LineNumber
                        << std::endl;

                    Okay =
                        false;
                }
                else if( !HaveLoop )
                {
                    std::cout
                        << "CLoopReader: 'startpose' before any 'loop' on line "
                        << LineNumber
                        << std::endl;

                    Okay =
                        false;
                }
                else
                {
                    // Convert once at the file boundary so all internal
                    // calculations consistently use radians.
                    mStartPose =
                        CPose
                        {
                            { X, Y },
                            HeadingDegrees
                                * mDegreesToRadians
                        };
                }
            }
            else if( Keyword == "vertex" )
            {
                float X =
                    0.0f;

                float Y =
                    0.0f;

                if( !( Words >> X >> Y ) )
                {
                    std::cout
                        << "CLoopReader: 'vertex' needs x and y on line "
                        << LineNumber
                        << std::endl;

                    Okay =
                        false;
                }
                else if( !HaveLoop )
                {
                    std::cout
                        << "CLoopReader: 'vertex' before any 'loop' on line "
                        << LineNumber
                        << std::endl;

                    Okay =
                        false;
                }
                else
                {
                    mVertices.push_back(
                        { X, Y } );
                }
            }
            else
            {
                std::cout
                    << "CLoopReader: unknown keyword '"
                    << Keyword
                    << "' on line "
                    << LineNumber
                    << std::endl;

                Okay =
                    false;
            }
        }
    }

    return Okay;
}