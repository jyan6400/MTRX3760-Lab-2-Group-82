/*
 * CRender.h
 *
 * This file declares the graphics and simple input wrapper used by A2. It
 * provides simulator-specific drawing, key and screenshot operations while
 * keeping all raylib-specific types and constants hidden.
 */

#ifndef CRENDER_H
#define CRENDER_H

//-----------------------------------------------------------------------------
// Vec2D
//
// Vec2D represents a two-dimensional coordinate used throughout the simulator
// without exposing raylib's Vector2 type.
//-----------------------------------------------------------------------------
struct Vec2D
{
    float x;
    float y;
};

//-----------------------------------------------------------------------------
// CRender
//
// CRender provides the graphics and simple input boundary for the simulator.
// CRender.cpp is the only source file that directly accesses raylib.
//-----------------------------------------------------------------------------
class CRender
{
    public:

        // Colours exposed through the simulator graphics interface.
        enum EColour
        {
            COLOUR_WHITE,
            COLOUR_BLUE,
            COLOUR_GREY
        };

        // Creates the simulator window and configures its target frame rate.
        CRender();

        // Returns true when the user requests that the window close.
        bool WindowShouldClose();

        // Returns true once when the user presses S.
        bool ScreenshotRequested() const;

        // Saves the currently displayed framebuffer to a PNG file.
        void SaveScreenshot(
            const char* aFilename ) const;

        // Closes the graphics window.
        void CloseWindow();

        // Begins and clears a rendered frame.
        void BeginDrawing();

        // Finishes the current rendered frame.
        void EndDrawing();

        // Draws a filled circle.
        void DrawCircle(
            Vec2D aPosition,
            int aRadius,
            EColour aColour );

        // Draws a straight line segment.
        void DrawLine(
            Vec2D aStart,
            Vec2D aEnd,
            float aThickness,
            EColour aColour );

        // Returns the configured graphics-window dimensions.
        int GetScreenWidth() const;
        int GetScreenHeight() const;

    private:

        // Internal colour representation prevents raylib's Color type from
        // appearing outside CRender.cpp.
        struct SColourComponents
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };

        // Converts a simulator colour into RGBA components.
        SColourComponents GetColourComponents(
            EColour aColour ) const;

        const int mScreenWidth;
        const int mScreenHeight;
};

#endif