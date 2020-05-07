/*
 * File:   TurnSignal.c
 * Author: Abraham
 *
 * Created on April 23, 2020, 2:15 PM
 */


#include "TurnSignal.h"

volatile bool ts_trigger = LOW;
bool cur_pc_input_state = false;
bool last_pc_input_state = false;

void TripTurnSignal()
{
    //SetOutputs( LOW );
    ts_trigger = HIGH;
}

const bool PatternCycleInputChanged()
{
    if ( cur_pc_input_state != last_pc_input_state )
    {
        uint delay_count = 0;
        
        while ( delay_count++ < 3 ) // must get n consecutive readings in a row
        {
            __delay_ms(10);
            // otherwise we ditch the reading
            if( pattern_cycle_GetValue() != cur_pc_input_state )
            {
                return false;
            }
        }
    }
    else
        return false;
    
    return true;
}