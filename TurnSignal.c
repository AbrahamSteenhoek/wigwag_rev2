#include "TurnSignal.h"

volatile bool ts_trigger = LOW;
unsigned long ts_trigger_time = 0;
bool cur_pc_input_state = false;
bool last_pc_input_state = false;

void TripTurnSignal()
{
    SetOutputs( LOW );
    ts_trigger_time = ms();
}

const bool TurnSignalDone()
{
//    // if the turn signal has been tripped again, reset the turn signal trigger time
    if ( turn_signal_GetValue() == HIGH )
    {
        SetOutputs( LOW );
        ts_trigger_time = ms();
        return false;
    }
    // proceed with flashing the pattern if the turn signal trigger time has not been tripped for TS_WAIT time
    return abs( ms() - ts_trigger_time ) > TS_WAIT;
}

const bool PatternCycleInputChanged()
{
    cur_pc_input_state = pattern_cycle_GetValue();
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
    {
        return false;
    }
    
    return true;
}