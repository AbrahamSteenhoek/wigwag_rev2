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
#include "status.h"

#include <xc.h>


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
    
//    L1_SetHigh();
//    L2_SetHigh();
//    L3_SetHigh();
//    L4_SetHigh();
    L1_SetLow();
    L2_SetLow();
    L3_SetLow();
    L4_SetLow();
}

uint8_t PatternCycleInputChanged()
{
    if ( cur_pc_input_state != last_pc_input_state )
    {
        uint16_t delay_count = 0;
        while ( delay_count++ < 3 )
        {
            __delay_ms(10);
            if( pattern_cycle_GetValue() != cur_pc_input_state )
            {
                return FALSE;
            }
        }
    }
    else
        return false;
    
    return true;
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
                L1_SetHigh();
                L2_SetHigh();
                L3_SetHigh();
                L4_SetHigh();
                
            }
            // if we have gone from PRESSED to RELEASED (using reverse logic)
            else
            {
                L1_SetLow();
                L2_SetLow();
                L3_SetLow();
                L4_SetLow();
            }
        }
        
        if( cur_ms - temp_ms > 1000 )
        {
            temp_ms = cur_ms;
            L1_Toggle();
        }
        
        last_pc_input_state = cur_pc_input_state;
    }
    return;
}
