#ifndef CRENDER_H
#define CRENDER_H

// A simple two-dimensional vector shared by the simulator classes.
struct Vec2D
{
    float x;
    float y;
};

// CRender is the only class that accesses raylib. The rest of the program uses
// this C++ interface and does not depend on raylib types or colour constants.
class CRender
{
    public:
        // Colours that the simulator can request without exposing raylib.
        enum EColour
        {
            COLOUR_WHITE,
            COLOUR_BLUE,
            COLOUR_GREY
        };

        CRender();

        // Returns whether the graphics window has been asked to close.
        bool WindowShouldClose();

        // Closes the graphics window.
        void CloseWindow();

        // Begins and ends one rendered frame.
        void BeginDrawing();
        void EndDrawing();

        // Draws simulator primitives without exposing raylib types.
        void DrawCircle(
            Vec2D aPosition,
            int aRadius,
            EColour aColour );

        void DrawLine(
            Vec2D aStart,
            Vec2D aEnd,
            float aThickness,
            EColour aColour );

        int GetScreenWidth() const;
        int GetScreenHeight() const;

    private:
        // Internal colour representation used to translate simulator colours
        // into raylib colours inside CRender.cpp.
        struct SColourComponents
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };

        SColourComponents GetColourComponents(
            EColour aColour ) const;

        const int mScreenWidth;
        const int mScreenHeight;
};

#endif