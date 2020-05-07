/*
 * File:   PatternSelector.c
 * Author: Abraham
 *
 * Created on April 23, 2020, 12:59 PM
 */

#include "PatternSelector.h"

void InitPatternSelector( struct PatternSelector* p_selector )
{
    InitWigwagPattern( p_selector->patterns[0] );
    p_selector->current_stage = p_selector->patterns[0]->first_stage;
}
