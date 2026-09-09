/*
 * CWheel.cpp
 *
 * This file implements the CWheel interface for storing and retrieving the
 * commanded speed of one independently controlled wheel.
 */

#include "CWheel.h"

//-----------------------------------------------------------------------------
void CWheel::SetSpeed( float aSpeed )
{
    mSpeed =
        aSpeed;
}

//-----------------------------------------------------------------------------
float CWheel::GetSpeed() const
{
    return mSpeed;
}