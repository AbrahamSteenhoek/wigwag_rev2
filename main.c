/*
 * File:   main.c
 * Author: Abraham
 *
 * Created on April 22, 2020, 1:02 PM
 */


/*
                         Main application
 */

#include "mcc_generated_files/mcc.h"

#include "Lights.h"
#include "PatternSelector.h"
#include "status.h"

#include <xc.h>

void SetOutputs( const bool state )
{
    SetLight( L1, state );
    SetLight( L2, state );
    SetLight( L3, state );
    SetLight( L4, state );
}

void setup()
{
    // initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // initialize the timer
    TMR1_Initialize();
    TMR1_StartTimer();

    // initialize pins to 0
    SetOutputs( LOW );
}

void main(void)
{
    setup();
    
    while(1)
    {
        cur_pc_input_state = pattern_cycle_GetValue();
        
        // only want to cycle the pattern when the user can see the pattern change (strobe is on)
        // if the buttonState has been changed
        // should trigger on button release
        if ( PatternCycleInputChanged() )
        {
            // gone from released to pressed
            if ( cur_pc_input_state == LOW )
            {
                SetOutputs( HIGH );
                //SetOutputs( HIGH );
            }
            // if we have gone from PRESSED to RELEASED (using reverse logic)
            else
            {
                SetOutputs( LOW );
                //SetOutputs( LOW );
            }
        }
                
        last_pc_input_state = cur_pc_input_state;
    }
    return;
}