#include "mcc_generated_files/mcc.h"

#include "Lights.h"
#include "PatternFlasher.h"
#include "PatternSelector.h"
#include "Pattern.h"
#include "Time.h"
#include "TurnSignal.h"

#include "assert.h"
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
    
//    InitPatternSelector();
    InitWigwagPattern( &Wigwag );
    current_stage = Wigwag.first_stage;
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
//                SetOutputs( HIGH );
//                SetLight(L1, HIGH);
//                SetLight(L2, HIGH);
//                L1_Toggle();
//                L2_Toggle();
            }
            // if we have gone from PRESSED to RELEASED (using reverse logic)
            else
            {
//                SetOutputs( LOW );
//                SetLight(L1, LOW);
//                SetLight(L2, LOW);
            }
        }
                
        last_pc_input_state = cur_pc_input_state;
        
        FlashPattern( &Wigwag );
    }
    return;
}
