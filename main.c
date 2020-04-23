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
    
    
    L1_SetLow();
    L2_SetLow();
    L3_SetLow();
    L4_SetLow();
}

void main(void)
{
    setup();
    
    while(1)
    {
        if ( pattern_cycle_GetValue() == HIGH )
            L1_SetHigh();
        else
            L1_SetLow();
    }
    return;
}
