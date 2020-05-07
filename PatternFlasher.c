/*
 * File:   PatternFlasher.c
 * Author: Abraham
 *
 * Created on May 6, 2020, 10:54 AM
 */


#include "PatternFlasher.h"

void FlashPattern( struct Pattern* pattern )
{
    uint current_time = cur_ms;
    
    if ( current_time - start_time > pattern_selector.current_stage->time_ms )
    {
        pattern_selector.current_stage = pattern_selector.current_stage->next;
        start_time = current_time;
        update_stage = true;
    }

    // Updating the lights to match the next stage
    if ( update_stage == true )
    {
        SetLight( L1, pattern_selector.current_stage->light_states[L1] );
        SetLight( L2, pattern_selector.current_stage->light_states[L2] );
        SetLight( L3, pattern_selector.current_stage->light_states[L3] );
        SetLight( L4, pattern_selector.current_stage->light_states[L4] );
        update_stage = false;
    }
}