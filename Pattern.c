/*
 * File:   Pattern.c
 * Author: Abraham
 *
 * Created on May 1, 2020, 6:49 PM
 */

#include <stdio.h>
#include "Pattern.h"

uint stage_list_iter = 0;

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

struct Stage* ConstructStage( const bool states[NUM_LIGHTS], const uint time_ms, struct Stage* next )
{
    struct Stage* new_stage = NewStage();
    AssignLightStates( new_stage, states );
    new_stage->time_ms = time_ms;
    new_stage->next = next;
    return new_stage;
}

struct Stage* CopyStage( struct Stage* dest, struct Stage* source )
{
    CopyStageData( dest, source );
    dest->next = source->next;
    return dest;
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

struct Stage* GetStage( struct Stage* head, uint num )
{
    struct Stage* get_stage = head;
    for( int i = 1; i < num; i++ )
        get_stage = get_stage->next;

    return get_stage;
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

    pattern->first_stage = NewStage();
    struct Stage* head = pattern->first_stage;

    // add 2 more repetitions of this
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), left_side_on ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }

    AppendStage( head, CopyStageData( NewStage(), off ) );
    // now add 3 repetitions of flashing the right side
    for( int i = 0; i < 3; i++ )
    {
        AppendStage( head, CopyStageData( NewStage(), right_side_on ) );
        AppendStage( head, CopyStageData( NewStage(), off ) );
    }

}
