#include "PatternSelector.h"

void InitPatternSelector( struct PatternSelector* p_selector )
{
    // Initialize all patterns as blank
    for ( int i = 0; i < MAX_PATTERNS; i++ )
    {
        p_selector->patterns[i] = NewPattern();
    }
    p_selector->active = WIGWAG;
    
    InitWigwagPattern( p_selector->patterns[WIGWAG] );
    InitXStrobePattern( p_selector->patterns[XSTROBE] );
    InitUpperLowerPattern( p_selector->patterns[UPPER_LOWER] );
    InitLowerPattern( p_selector->patterns[LOWER] );
    p_selector->current_stage = p_selector->patterns[ p_selector->active ]->first_stage;
    
    p_selector->start_time = 0;
}

struct Pattern* ActivePattern( struct PatternSelector* p )
{
    return p->patterns[ p->active ];
}

struct Pattern* NextPattern( struct PatternSelector* p_selector )
{
    switch( p_selector->active )
    {
        case WIGWAG:
            p_selector->active = XSTROBE;
            break;
        case XSTROBE:
            p_selector->active = UPPER_LOWER;
            break;
        case UPPER_LOWER:
            p_selector->active = LOWER;
            break;
        case LOWER:
            p_selector->active = WIGWAG;
            break;
        default:
            p_selector->active = WIGWAG;
            break;
    }
    
    p_selector->current_stage = p_selector->patterns[ p_selector->active ]->first_stage;
    
    return p_selector->patterns[ p_selector->active ];
}
