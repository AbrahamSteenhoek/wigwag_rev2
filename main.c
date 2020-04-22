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
    
    
    L1_SetHigh();
    L2_SetHigh();
    L3_SetHigh();
    L4_SetHigh();
}

void main(void)
{
    setup();
    while(1)
    {
        if ( count - temp > 1000 )
        {
            temp = count;
            L1_Toggle();
            L2_Toggle();
            L3_Toggle();
            L4_Toggle();
        }
    }
    return;
}
