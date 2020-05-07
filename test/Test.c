#include "Test.h"

int setupPatternTestSuite(void) {
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("Pattern Test Suite", initPatternTestSuite, cleanPatternTestSuite);
    if (NULL == pSuite)
        return -1;
    CU_add_test( pSuite, "testNewStageOverflow()", testNewStageOverflow );
    CU_add_test( pSuite, "testStageInitialization()", testStageInitialization );
    CU_add_test( pSuite, "testStageConstruction()", testStageConstruction );
    CU_add_test( pSuite, "testCopyStage()", testCopyStage );
    CU_add_test( pSuite, "testAppendStage()", testAppendStage );
    CU_add_test( pSuite, "testNewPattern()", testNewPattern );
    CU_add_test( pSuite, "testInitWigwagPattern()", testInitWigwagPattern );
    CU_add_test( pSuite, "testInitPatternSelector()", testInitPatternSelector );

    return 0;
}

void FlushStageStash( void )
{
    stage_list_iter = 0;
    while( NewStage() != NULL )
        ;
    stage_list_iter = 0;
}

void CompareStageData( const struct Stage* stage1, const struct Stage* stage2 )
{
    for( int i = 0; i < NUM_LIGHTS; i++ )
    {
        CU_ASSERT( stage1->light_states[i] == stage2->light_states[i] );
    }
    CU_ASSERT( stage1->time_ms == stage2->time_ms );
}

void CompareStage( const struct Stage* stage1, const struct Stage* stage2 )
{
    CompareStageData( stage1, stage2 );
    CU_ASSERT_PTR_EQUAL( stage1->next, stage2->next );
}

void StagesAreSame( const struct Stage* stage1, const struct Stage* stage2 )
{
    CU_ASSERT_PTR_EQUAL( stage1, stage2 );
    CompareStage( stage1, stage2 );
}

int initPatternTestSuite(void)
{
    return 0;
}

int cleanPatternTestSuite(void)
{
    return 0;
}

void testNewStageOverflow( void )
{
    stage_list_iter = 0;
    for( int i = 0; i < MAX_STAGES; i++ )
    {
        CU_ASSERT_PTR_NOT_NULL( NewStage() );
    }

    CU_ASSERT_PTR_NULL( NewStage() );
}

void testStageInitialization( void )
{
    stage_list_iter = 0;
    uint prev_iter_pos = stage_list_iter;

    struct Stage* stage = NewStage();
    CU_ASSERT( prev_iter_pos + 1 == stage_list_iter );
    CU_ASSERT_PTR_NOT_NULL( stage );

    for( int i = 0; i < NUM_LIGHTS; i++ )
    {
        CU_ASSERT( stage->light_states[i] == OFF );
    }

    CU_ASSERT( stage->time_ms == DEFAULT_INTERVAL );
}

void testStageConstruction( void )
{
    bool temp_states[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage *stage = ConstructStage( temp_states, 100, NULL );

    CU_ASSERT( stage->light_states[L1] == ON );
    CU_ASSERT( stage->light_states[L2] == OFF );
    CU_ASSERT( stage->light_states[L3] == ON );
    CU_ASSERT( stage->light_states[L4] == OFF );

    CU_ASSERT( stage->time_ms == 100 );
    CU_ASSERT_PTR_NULL( stage->next );
}

void testCopyStage( void )
{
    FlushStageStash();
    struct Stage* stage1 = NewStage();
    CU_ASSERT_PTR_NULL( stage1->next );

    bool temp_states[NUM_LIGHTS] = { ON, ON, ON, ON };
    struct Stage *stage2 = ConstructStage( temp_states, 100, NULL );
    stage2->next = stage2;
    CU_ASSERT_PTR_NOT_NULL( stage2->next );

    for( int i = 0; i < NUM_LIGHTS; i++ )
        CU_ASSERT( stage1->light_states[i] != stage2->light_states[i] );
    CU_ASSERT( stage1->time_ms != stage2->time_ms );

    CopyStage( stage1, stage2 );
    CompareStage( stage1, stage2 );
}

void testAppendStage( void )
{
    FlushStageStash();
    struct Stage* head = NewStage();
    CU_ASSERT_PTR_NULL( head->next );

    bool states2[NUM_LIGHTS] = { ON, ON, ON, ON };
    struct Stage *stage2 = ConstructStage( states2, 100, NULL );

    AppendStage( head, stage2 );
    CU_ASSERT_PTR_EQUAL( head->next, stage2 );
    CU_ASSERT_PTR_EQUAL( stage2->next, head );
    StagesAreSame( head->next, stage2 );

    bool states3[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage* stage3 = ConstructStage( states3, 178, NULL );

    AppendStage( head, stage3 );
    CU_ASSERT_PTR_EQUAL( stage3->next, head );

    StagesAreSame( head->next, stage2 );
    StagesAreSame( stage2->next, stage3);

    struct Stage* stage4 = NewStage();
    CopyStage( stage4, stage2 );
    AppendStage( head, stage4 );

    CU_ASSERT_PTR_EQUAL( head->next, stage2 );
    CU_ASSERT_PTR_EQUAL( stage2->next, stage3 );
    CU_ASSERT_PTR_EQUAL( stage3->next, stage4 );
    CU_ASSERT_PTR_EQUAL( stage4->next, head );

    for( int i = 0; i < NUM_LIGHTS; i++ )
        CU_ASSERT( stage4->light_states[i] == stage2->light_states[i] );
    CU_ASSERT( stage4->time_ms == stage2->time_ms );

    CU_ASSERT_PTR_EQUAL( stage3, GetStage( head, 3 ) );
}

void testNewPattern( void )
{
    FlushStageStash();
    struct Pattern* wigwag = NewPattern();
    CompareStageData( wigwag->first_stage, NewStage() );
    CU_ASSERT( wigwag->name == WIGWAG );
    CU_ASSERT_PTR_NULL( wigwag->first_stage->next );
}

void testInitWigwagPattern( void )
{
    FlushStageStash();
    //struct Pattern wigwag;
    struct Pattern* wigwag = NewPattern();
    InitWigwagPattern( wigwag );

    bool left_side_states[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage* left_side_on = ConstructStage( left_side_states, DEFAULT_INTERVAL, NULL );
    bool right_side_states[NUM_LIGHTS] = { OFF, ON, OFF, ON };
    struct Stage* right_side_on = ConstructStage( right_side_states, DEFAULT_INTERVAL, NULL );
    struct Stage* off = NewStage();

    CompareStageData( GetStage( wigwag->first_stage, 1  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 2  ), left_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 3  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 4  ), left_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 5  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 6  ), left_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 7  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 8  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 9  ), right_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 10 ), off );
    CompareStageData( GetStage( wigwag->first_stage, 11 ), right_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 12 ), off );
    CompareStageData( GetStage( wigwag->first_stage, 13 ), right_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 14 ), off );
    CU_ASSERT_PTR_EQUAL( GetStage( wigwag->first_stage, 14 )->next, wigwag->first_stage );

    struct Stage* current_stage = wigwag->first_stage;
    int i = 1;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, left_side_on );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, left_side_on );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, left_side_on );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, right_side_on );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, right_side_on );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, right_side_on );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( wigwag->first_stage, i++ ) );
    current_stage = current_stage->next;
    CU_ASSERT_PTR_EQUAL( current_stage, wigwag->first_stage );
}

void testInitPatternSelector( void )
{
    FlushStageStash();
    struct PatternSelector p;
    InitPatternSelector( &p );

    struct Pattern* wigwag = p.patterns[0];

    bool left_side_states[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage* left_side_on = ConstructStage( left_side_states, DEFAULT_INTERVAL, NULL );
    bool right_side_states[NUM_LIGHTS] = { OFF, ON, OFF, ON };
    struct Stage* right_side_on = ConstructStage( right_side_states, DEFAULT_INTERVAL, NULL );
    struct Stage* off = NewStage();

    CompareStageData( GetStage( wigwag->first_stage, 1  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 2  ), left_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 3  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 4  ), left_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 5  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 6  ), left_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 7  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 8  ), off );
    CompareStageData( GetStage( wigwag->first_stage, 9  ), right_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 10 ), off );
    CompareStageData( GetStage( wigwag->first_stage, 11 ), right_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 12 ), off );
    CompareStageData( GetStage( wigwag->first_stage, 13 ), right_side_on );
    CompareStageData( GetStage( wigwag->first_stage, 14 ), off );
    CU_ASSERT_PTR_EQUAL( GetStage( wigwag->first_stage, 14 )->next, wigwag->first_stage );
}
