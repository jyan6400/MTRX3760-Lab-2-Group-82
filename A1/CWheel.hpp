// CWheel is the class responsible for controlling and 
// regulating the speed of the wheels
#ifndef CWHEEL_HPP
#define CWHEEL_HPP

class CWheel
{
    public:
        // Regulate the wheel speed
        void SetSpeed( float aSpeed );

        // Get the current speed value
        float GetSpeed() const;

    private:
        // Wheel's current speed
        float mSpeed{ 0.0f };
};

#endif