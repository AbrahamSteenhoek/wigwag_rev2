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
//#include "Pattern.h"
#include "Time.h"
#include "TurnSignal.h"

#include "assert.h"
#include <xc.h>

void setup()
{
    //assert( 1 == 0 );
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
            }
            // if we have gone from PRESSED to RELEASED (using reverse logic)
            else
            {
                SetOutputs( LOW );
            }
        }
                
        last_pc_input_state = cur_pc_input_state;
    }
    return;
}
