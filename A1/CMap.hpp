// CMap is the class responsible for loading wall data, rendering walls,
// conducting collision detection for robots, and calculating the distance
// of sensors.
#ifndef CMAP_HPP
#define CMAP_HPP

#include <string>
#include <vector>
#include "CRender.h"
#include "CLoopReader.h"

// Indicates the two dimensional wall
struct Wall {
    // The coordinate of starting point
    Vec2D mStart;

    // The coordinate of ending point
    Vec2D mEnd;
};

class CMap
{
public:
    // Load the Map file 
    bool Load( const std::string& aFilename );

    // Obtain the initial pose of the robot as defined in the map
    const CPose& GetStartPose() const;
    
    // Check if the robot collides with any walls
    bool CheckCollision( const Vec2D& aPosition, float aRadius ) const;

    // Cast a ray and find the distance to the nearest wall it hits
    float GetRayIntersection( const Vec2D& aStartPosition, float aRayAngle ) const;

    // Draw all the walls on the screen
    void Draw( CRender& aRender ) const;

private:
    // Build wall data
    void BuildWalls();

    CLoopReader mLoopReader;

    // List of wall line segments
    std::vector<Wall> mWalls;

    // The maximum detection distance threshold of the sensor
    const float mMaxRange{ 2000.0f };
};

#endif