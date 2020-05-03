/*
 * File:   Pattern.c
 * Author: Abraham
 *
 * Created on May 1, 2020, 6:49 PM
 */

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
    struct Stage* new_stage = &stage_stash[ stage_list_iter++ ];
    bool temp_states[NUM_LIGHTS] = { OFF, OFF, OFF, OFF };
    AssignLightStates( new_stage, temp_states );
    new_stage->time_ms = DEFAULT_INTERVAL;
    
    return new_stage;
}

struct Stage* ConstructStage( const bool states[NUM_LIGHTS], const uint time_ms )
{
    struct Stage* new_stage = NewStage();
    AssignLightStates( new_stage, states );
    new_stage->time_ms = time_ms;
    new_stage->next = NULL;
    return new_stage;
}

void InitStageList( struct Stage* head, struct Stage* first_stage )
{
    head = first_stage;
    head->next = NULL;
}

void AppendStage( struct Stage* head, struct Stage* new_stage )
{
    if ( head->next == 0  ) // if the list of stages is only the first stage (adding the first item to the list)
    {
        head->next = new_stage;
        new_stage->next = head;
    }
    else // if the stage list has more than 1 stage
    {
        struct Stage* last_stage = head->next;
        while( last_stage->next != 0 ) // iterate over to the last stage
            last_stage = last_stage->next;

        // now last_stage points to the last stage in the list
        last_stage->next = new_stage; // append the new stage onto the end
        new_stage->next = head;
    }
}

void InitWigwagPattern( struct Pattern* pattern )
{
    pattern->name = WIGWAG;
    
    bool temp_states[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage *stage1 = ConstructStage( temp_states, 100 );
    InitStageList( pattern->stage_list, stage1 );
    
    struct Stage *stage2 = NewStage();
    (void)stage2;
    (void)AppendStage(NULL, NULL);
    //stage1->light_states = { OFF, OFF, OFF, OFF };
    
    for ( uint i = 0; i < 3 ; i++ )
    {
    }
    
    
}