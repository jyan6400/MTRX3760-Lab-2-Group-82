#ifndef CWHEEL_H
#define CWHEEL_H

// CWheel stores the commanded speed of one independently controlled wheel.
class CWheel
{
    public:
        // Sets the commanded wheel speed.
        void SetSpeed( float aSpeed );

        // Returns the current commanded wheel speed.
        float GetSpeed() const;

    private:
        float mSpeed{ 0.0f };
};

#endif