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
    
    if ( current_time - start_time > current_stage->time_ms )
    {
        current_stage = current_stage->next;
        start_time = current_time;
        update_stage = true;
    }

    // Updating the lights to match the next stage
    if ( update_stage == true )
    {
        SetLight( L1, current_stage->light_states[L1] );
        SetLight( L2, current_stage->light_states[L2] );
        SetLight( L3, current_stage->light_states[L3] );
        SetLight( L4, current_stage->light_states[L4] );
        update_stage = false;
    }
}