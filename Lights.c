/*
 * File:   Lights.c
 * Author: Abraham
 *
 * Created on April 23, 2020, 1:43 PM
 */


#include "Lights.h"

// Uses a mapping from light enumeration to pin
void SetLight( const enum Light light, const bool state )
{
    // important: The switch statement is necessary because the pin# and the Light# are not always in correspondence
    switch ( light )
    {
        case L1:
            SET( L1_LAT, state );
        case L2:
            SET( L2_LAT, state );
        case L3:
            SET( L3_LAT, state );
        case L4:
        default:
            SET( L4_LAT, state );
            break;
    }
}

void SetOutputs( const bool state )
{
    SetLight( L1, state );
    SetLight( L2, state );
    SetLight( L3, state );
    SetLight( L4, state );
}
