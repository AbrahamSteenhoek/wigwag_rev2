/*
 * File:   PatternSelector.c
 * Author: Abraham
 *
 * Created on April 23, 2020, 12:59 PM
 */

#include "PatternSelector.h"

void InitPatternSelector( struct PatternSelector* p_selector )
{
    // Initialize all patterns as blank
    for ( int i = 0; i < MAX_PATTERNS; i++ )
    {
        p_selector->patterns[i] = NewPattern();
    }
    InitWigwagPattern( p_selector->patterns[0] );
    p_selector->current_stage = p_selector->patterns[0]->first_stage;
}
