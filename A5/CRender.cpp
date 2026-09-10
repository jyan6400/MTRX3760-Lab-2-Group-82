/*
 * CRender.cpp
 *
 * This file implements the graphics, window and screenshot operations provided
 * by CRender. All direct interaction with raylib is contained in this file.
 */

#include "CRender.h"

#include <raylib.h>


//-----------------------------------------------------------------------------
CRender::CRender()
{
    ::InitWindow(
        mScreenWidth,
        mScreenHeight,
        "MTRX3760 Lab 2 - A5 Noise Simulation" );

    ::SetTargetFPS( mTargetFramesPerSecond );
}


//-----------------------------------------------------------------------------
bool CRender::WindowShouldClose() const
{
    bool ShouldClose =
        ::WindowShouldClose();

    return ShouldClose;
}


//-----------------------------------------------------------------------------
void CRender::BeginDrawing() const
{
    ::BeginDrawing();

    // Persistent robot paths are stored explicitly by CTrail, so the display
    // can be cleared safely at the beginning of every rendered frame.
    ::ClearBackground( BLACK );
}


//-----------------------------------------------------------------------------
void CRender::EndDrawing() const
{
    ::EndDrawing();
}


//-----------------------------------------------------------------------------
void CRender::CloseWindow() const
{
    ::CloseWindow();
}


//-----------------------------------------------------------------------------
void CRender::DrawCircle(
    const Vec2D& aCentre,
    float aRadius,
    EColour aColour ) const
{
    Color RayColour =
        WHITE;

    // Convert simulator colours to raylib colours only inside the rendering
    // wrapper so raylib-specific types do not escape into the simulator.
    switch( aColour )
    {
        case COLOUR_WHITE:
        {
            RayColour = WHITE;
            break;
        }

        case COLOUR_BLUE:
        {
            RayColour = BLUE;
            break;
        }

        case COLOUR_GREY:
        {
            RayColour = GRAY;
            break;
        }
    }

    const Vector2 Centre =
    {
        aCentre.x,
        aCentre.y
    };

    ::DrawCircleV(
        Centre,
        aRadius,
        RayColour );
}


//-----------------------------------------------------------------------------
void CRender::DrawLine(
    const Vec2D& aStart,
    const Vec2D& aEnd,
    float aThickness,
    EColour aColour ) const
{
    Color RayColour =
        WHITE;

    // Convert the simulator colour to the corresponding raylib colour.
    switch( aColour )
    {
        case COLOUR_WHITE:
        {
            RayColour = WHITE;
            break;
        }

        case COLOUR_BLUE:
        {
            RayColour = BLUE;
            break;
        }

        case COLOUR_GREY:
        {
            RayColour = GRAY;
            break;
        }
    }

    const Vector2 Start =
    {
        aStart.x,
        aStart.y
    };

    const Vector2 End =
    {
        aEnd.x,
        aEnd.y
    };

    ::DrawLineEx(
        Start,
        End,
        aThickness,
        RayColour );
}


//-----------------------------------------------------------------------------
bool CRender::ScreenshotRequested() const
{
    bool Requested =
        ::IsKeyPressed( KEY_S );

    return Requested;
}


//-----------------------------------------------------------------------------
void CRender::SaveScreenshot( const char* aFilename ) const
{
    ::TakeScreenshot( aFilename );
}