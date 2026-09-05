// CSimulation is the class responsible for integrating graphic rendering, 
// map loading, robot update and terminal summary output
#ifndef CSIMULATION_HPP
#define CSIMULATION_HPP

#include <string>
#include "CRender.h"
#include "CMap.hpp"
#include "CWallFollower.hpp"

class CSimulation
{
    public:
        // Initialise the map
        CSimulation( const std::string& aFilename );

        // Run the main loop until the window is closed, 
        // and print the report at the end.
        void Run();

    private:
        void Update( float aDt );
        void Render();
        void Report() const;

        CRender mRender;
        CMap mMap;
        CWallFollower mRobot;

        // Record the total number of simulation update steps
        int mTotalUpdates{ 0 };
        
        // Fixed time step, independent of the actual time of the system
        const float mFixedDt{ 1.0f / 60.0f };
};

#endif 