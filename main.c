#include "mcc_generated_files/mcc.h"

#include "Lights.h"
#include "PatternFlasher.h"
#include "PatternSelector.h"
#include "Pattern.h"
#include "Time.h"
#include "TurnSignal.h"

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

    // initialize pins to 0
    SetOutputs( LOW );
    
    InitPatternSelector( &pattern_selector );
}

void main(void)
{
    setup();
    
    while(1)
    {
        if( !TurnSignalDone() )
            continue;
        
//        if ( turn_signal_GetValue() == HIGH )
//        {
//            L2_SetHigh();
//        }
//        else
//        {
//            L2_SetLow();
//        }
        // only want to cycle the pattern when the user can see the pattern change (strobe is on)
        // if the buttonState has been changed
        // should trigger on button release
        if ( PatternCycleInputChanged() )
        {
            // gone from released to pressed (using reverse logic)
            if ( cur_pc_input_state == LOW )
            {
                NextPattern( &pattern_selector );
            }
            // if we have gone from PRESSED to RELEASED (using reverse logic)
            else
            {
            }
        }

        last_pc_input_state = cur_pc_input_state;
        
        FlashPattern();
    }
    return;
}
