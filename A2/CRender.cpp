/*
 * CRender.cpp
 *
 * This file implements the A2 graphics and input wrapper. It is intentionally
 * the only source file that includes raylib.h or directly accesses raylib
 * types, constants and functions.
 */

#include "CRender.h"

#include "raylib.h"

//-----------------------------------------------------------------------------
CRender::CRender()
    :
        mScreenWidth( 800 ),
        mScreenHeight( 600 )
{
    ::InitWindow(
        mScreenWidth,
        mScreenHeight,
        "MTRX3760 Lab 2 - Wall and Line Followers" );

    ::SetTargetFPS(
        60 );
}

//-----------------------------------------------------------------------------
int CRender::GetScreenWidth() const
{
    return mScreenWidth;
}

//-----------------------------------------------------------------------------
int CRender::GetScreenHeight() const
{
    return mScreenHeight;
}

//-----------------------------------------------------------------------------
bool CRender::WindowShouldClose()
{
    bool Result =
        ::WindowShouldClose();

    return Result;
}

//-----------------------------------------------------------------------------
bool CRender::ScreenshotRequested() const
{
    // Keep the raylib key constant behind the CRender abstraction.
    bool Result =
        ::IsKeyPressed( KEY_S );

    return Result;
}

//-----------------------------------------------------------------------------
void CRender::SaveScreenshot(
    const char* aFilename ) const
{
    ::TakeScreenshot(
        aFilename );
}

//-----------------------------------------------------------------------------
void CRender::CloseWindow()
{
    ::CloseWindow();
}

//-----------------------------------------------------------------------------
void CRender::BeginDrawing()
{
    ::BeginDrawing();

    ::ClearBackground(
        BLACK );
}

//-----------------------------------------------------------------------------
void CRender::EndDrawing()
{
    ::EndDrawing();
}

//-----------------------------------------------------------------------------
CRender::SColourComponents CRender::GetColourComponents(
    EColour aColour ) const
{
    SColourComponents Result
    {
        255,
        255,
        255,
        255
    };

    if( aColour == COLOUR_BLUE )
    {
        Result =
            SColourComponents
            {
                0,
                121,
                241,
                255
            };
    }
    else if( aColour == COLOUR_GREY )
    {
        Result =
            SColourComponents
            {
                130,
                130,
                130,
                255
            };
    }

    return Result;
}

//-----------------------------------------------------------------------------
void CRender::DrawCircle(
    Vec2D aPosition,
    int aRadius,
    EColour aColour )
{
    // Translation to raylib-owned types occurs only at this wrapper boundary.
    SColourComponents Components =
        GetColourComponents(
            aColour );

    Color RayColour
    {
        Components.r,
        Components.g,
        Components.b,
        Components.a
    };

    ::DrawCircle(
        aPosition.x,
        aPosition.y,
        aRadius,
        RayColour );
}

//-----------------------------------------------------------------------------
void CRender::DrawLine(
    Vec2D aStart,
    Vec2D aEnd,
    float aThickness,
    EColour aColour )
{
    SColourComponents Components =
        GetColourComponents(
            aColour );

    Color RayColour
    {
        Components.r,
        Components.g,
        Components.b,
        Components.a
    };

    Vector2 Start
    {
        aStart.x,
        aStart.y
    };

    Vector2 End
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