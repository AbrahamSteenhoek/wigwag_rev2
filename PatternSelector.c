/*
 * File:   PatternSelector.c
 * Author: Abraham
 *
 * Created on April 23, 2020, 12:59 PM
 */

#include "PatternSelector.h"

const bool PatternCycleInputChanged()
{
    if ( cur_pc_input_state != last_pc_input_state )
    {
        uint16_t delay_count = 0;
        
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
