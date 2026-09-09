#include "CRender.h"

#include "raylib.h"

CRender::CRender()
    :
        mScreenWidth( 800 ),
        mScreenHeight( 600 )
{
    ::InitWindow(
        mScreenWidth,
        mScreenHeight,
        "MTRX3760 Lab 2 - A5 Noise Simulation" );

    ::SetTargetFPS( 60 );
}

int CRender::GetScreenWidth() const
{
    return mScreenWidth;
}

int CRender::GetScreenHeight() const
{
    return mScreenHeight;
}

bool CRender::WindowShouldClose()
{
    bool Result =
        ::WindowShouldClose();

    return Result;
}

void CRender::CloseWindow()
{
    ::CloseWindow();
}

void CRender::BeginDrawing()
{
    ::BeginDrawing();

    ::ClearBackground(
        BLACK );
}

void CRender::EndDrawing()
{
    ::EndDrawing();
}

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

void CRender::DrawCircle(
    Vec2D aPosition,
    int aRadius,
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

    ::DrawCircle(
        aPosition.x,
        aPosition.y,
        aRadius,
        RayColour );
}

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