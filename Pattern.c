/*
 * File:   Pattern.c
 * Author: Abraham
 *
 * Created on May 1, 2020, 6:49 PM
 */

#include <stdio.h>
#include "Pattern.h"

uint stage_list_iter = 0;
uint pattern_list_iter = 0;

void AssignLightStates( struct Stage* stage, const bool states[ NUM_LIGHTS ] )
{
    for( uint i = 0; i < NUM_LIGHTS; i++ )
    {
        stage->light_states[i] = states[i];
    }
}

struct Stage* NewStage() // returns the address of the next empty stage available in the stash
{
    if ( stage_list_iter >= MAX_STAGES )
        return NULL;

    struct Stage* new_stage = &stage_stash[ stage_list_iter++ ];
    bool init_states[NUM_LIGHTS] = { OFF, OFF, OFF, OFF };
    AssignLightStates( new_stage, init_states );
    new_stage->time_ms = DEFAULT_INTERVAL;
    new_stage->next = NULL;

    return new_stage;
}

struct Pattern* NewPattern()
{
    if ( pattern_list_iter >= MAX_PATTERNS )
    {
        return NULL;
    }
    struct Pattern* new_pattern = &pattern_stash[ pattern_list_iter++ ];
    new_pattern->name = WIGWAG;
    new_pattern->first_stage = NewStage();
    
    return new_pattern;
}

struct Stage* ConstructStage( const bool states[NUM_LIGHTS], const uint time_ms, struct Stage* next )
{
    struct Stage* new_stage = NewStage();
    AssignLightStates( new_stage, states );
    new_stage->time_ms = time_ms;
    new_stage->next = next;
    return new_stage;
}

struct Stage* CopyStageData( struct Stage* dest, struct Stage* source )
{
    for( int i = 0; i < NUM_LIGHTS; i++ )
        dest->light_states[i] = source->light_states[i];
    dest->time_ms = source->time_ms;    
    return dest;
}

void AppendStage( struct Stage* head, struct Stage* new_stage )
{
    if ( head->next == NULL  ) // if the list of stages is only the first stage (adding the first item to the list)
    {
        head->next = new_stage;
        new_stage->next = head;
    }
    else // if the stage list has more than 1 stage
    {
        struct Stage* last_stage = head->next;
        while( last_stage->next != head ) // iterate over to the last stage
            last_stage = last_stage->next;

        // now last_stage points to the last stage in the list
        last_stage->next = new_stage; // append the new stage onto the end
        new_stage->next = head;
    }
}

void InitWigwagPattern( struct Pattern* pattern )
{
    pattern->name = WIGWAG;

    // Stage that turns on the Left Side
    bool left_side_states[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage* left_side_on = ConstructStage( left_side_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns on the Right Side
    bool right_side_states[NUM_LIGHTS] = { OFF, ON, OFF, ON };
    struct Stage* right_side_on = ConstructStage( right_side_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns off all lights
    struct Stage* off = NewStage();    

    struct Stage* head = pattern->first_stage;

    // add 3 flashes on the left side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), left_side_on ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }

    // add a rest before switching to the right side
    AppendStage( head, CopyStageData( NewStage(), off ) );

    // now add 3 flashes on the right side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), right_side_on ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }
}

void InitXStrobePattern( struct Pattern* pattern )
{
    pattern->name = XSTROBE;

    // Stage that turns on the diagonal of lights 1 & 4
    bool diag_1_4_states[NUM_LIGHTS] = { ON, OFF, OFF, ON };
    struct Stage* diag_1_4 = ConstructStage( diag_1_4_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns on the diagonal of lights 2 & 3
    bool diag_2_3_states[NUM_LIGHTS] = { OFF, ON, ON, OFF };
    struct Stage* diag_2_3 = ConstructStage( diag_2_3_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns off all lights
    struct Stage* off = NewStage();    

    struct Stage* head = pattern->first_stage;

    // add 3 flashes on the first diag
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), diag_1_4 ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }

    // add a rest before switching to the other diag
    AppendStage( head, CopyStageData( NewStage(), off ) );

    // now add 3 flashes on the second diag
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), diag_2_3 ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }
}

void InitUpperLowerPattern( struct Pattern* pattern )
{
    pattern->name = UPPER_LOWER;

    // Stage that turns on the upper lights
    bool upper_states[NUM_LIGHTS] = { ON, ON, OFF, OFF };
    struct Stage* upper = ConstructStage( upper_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns on the lower lights
    bool lower_states[NUM_LIGHTS] = { OFF, OFF, ON, ON };
    struct Stage* lower = ConstructStage( lower_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns off all lights
    struct Stage* off = NewStage();    

    //pattern->first_stage = NewStage();
    struct Stage* head = pattern->first_stage;

    // add 3 flashes on the upper side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), upper ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }

    // add a rest before switching to the right side
    AppendStage( head, CopyStageData( NewStage(), off ) );

    // now add 3 flashes on the lower side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), lower ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }
}

void InitLowerPattern( struct Pattern* pattern )
{
    pattern->name = LOWER;

    // Stage that turns on the lower left light
    bool lower_left_states[NUM_LIGHTS] = { OFF, OFF, ON, OFF };
    struct Stage* lower_left = ConstructStage( lower_left_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns on the lower right light
    bool lower_right_states[NUM_LIGHTS] = { OFF, OFF, OFF, ON };
    struct Stage* lower_right = ConstructStage( lower_right_states, DEFAULT_INTERVAL, NULL );
    // Stage that turns off all lights
    struct Stage* off = NewStage();    

    struct Stage* head = pattern->first_stage;

    // add 3 flashes on the left side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), lower_left ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }

    // add a rest before switching to the right side
    AppendStage( head, CopyStageData( NewStage(), off ) );

    // now add 3 flashes on the right side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), lower_right ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }
}