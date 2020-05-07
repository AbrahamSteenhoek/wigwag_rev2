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
            if ( L1_GetValue() != state )
                L1_Toggle();
            break;
        case L2:
            if ( L2_GetValue() != state )
                L2_Toggle();
            break;
        case L3:
            if ( L3_GetValue() != state )
                L3_Toggle();
            break;
        case L4:
        default:
            if ( L4_GetValue() != state )
                L4_Toggle();
            break;
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
