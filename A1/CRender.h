/*
 * CRender.h
 *
 * This file declares CRender, which provides the graphics interface used by
 * the simulator while hiding all raylib-specific types and functions.
 */

#ifndef CRENDER_H
#define CRENDER_H


//-----------------------------------------------------------------------------
// A simple two-dimensional vector used throughout the simulator.
struct Vec2D
{
    float x;
    float y;
};


//-----------------------------------------------------------------------------
// CRender provides drawing, window and screenshot operations without exposing
// raylib-specific types to the rest of the simulator.
class CRender
{
    public:

        // Colours required by the simulator.
        enum EColour
        {
            COLOUR_WHITE,
            COLOUR_BLUE,
            COLOUR_GREY
        };

        CRender();

        // Returns true when the user requests that the window be closed.
        bool WindowShouldClose() const;

        // Begins a new frame and clears the previous frame.
        void BeginDrawing() const;

        // Completes the current frame.
        void EndDrawing() const;

        // Closes the graphics window.
        void CloseWindow() const;

        // Draws a filled circle at the supplied simulator position.
        void DrawCircle(
            const Vec2D& aCentre,
            float aRadius,
            EColour aColour ) const;

        // Draws a line of the supplied thickness between two positions.
        void DrawLine(
            const Vec2D& aStart,
            const Vec2D& aEnd,
            float aThickness,
            EColour aColour ) const;

        // Returns true once when the screenshot key is pressed.
        bool ScreenshotRequested() const;

        // Saves the current window contents to the supplied filename.
        void SaveScreenshot( const char* aFilename ) const;

    private:

        // Window configuration.
        const int mScreenWidth{ 800 };
        const int mScreenHeight{ 600 };
        const int mTargetFramesPerSecond{ 60 };
};


#endif