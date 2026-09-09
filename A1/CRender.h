/*
 * CRender.h
 *
 * This file declares the graphics wrapper used by the simulator. It provides a
 * small C++ drawing and input interface while keeping raylib-specific types,
 * constants and functions hidden from the rest of the program.
 */

#ifndef CRENDER_H
#define CRENDER_H

//-----------------------------------------------------------------------------
// Vec2D
//
// Vec2D represents a simple two-dimensional coordinate used throughout the
// simulator without exposing raylib's Vector2 type.
//-----------------------------------------------------------------------------
struct Vec2D
{
    float x;
    float y;
};

//-----------------------------------------------------------------------------
// CRender
//
// CRender provides the simulator graphics and simple input interface. Other
// classes request drawing, key and screenshot operations using simulator-owned
// types, while CRender.cpp performs all direct interaction with raylib.
//-----------------------------------------------------------------------------
class CRender
{
    public:

        // Colours exposed by the simulator graphics interface.
        enum EColour
        {
            COLOUR_WHITE,
            COLOUR_BLUE,
            COLOUR_GREY
        };

        // Creates the simulator window and configures its target frame rate.
        CRender();

        // Returns true when the graphics window has been requested to close.
        bool WindowShouldClose();

        // Returns true once when the user presses the S key.
        bool ScreenshotRequested() const;

        // Saves the current graphics window contents to a PNG file.
        void SaveScreenshot( const char* aFilename ) const;

        // Closes the graphics window.
        void CloseWindow();

        // Begins a new rendered frame and clears the previous image.
        void BeginDrawing();

        // Finishes the current rendered frame.
        void EndDrawing();

        // Draws a filled circle using simulator coordinates and colours.
        void DrawCircle(
            Vec2D aPosition,
            int aRadius,
            EColour aColour );

        // Draws a straight line between two simulator coordinates.
        void DrawLine(
            Vec2D aStart,
            Vec2D aEnd,
            float aThickness,
            EColour aColour );

        // Returns the configured window dimensions.
        int GetScreenWidth() const;
        int GetScreenHeight() const;

    private:

        // Internal colour representation prevents raylib's Color type from
        // appearing in this public header.
        struct SColourComponents
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };

        // Converts a simulator colour into RGBA components for raylib.
        SColourComponents GetColourComponents(
            EColour aColour ) const;

        // Fixed dimensions of the simulator window.
        const int mScreenWidth;
        const int mScreenHeight;
};

#endif