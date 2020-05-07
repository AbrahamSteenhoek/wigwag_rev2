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
    CU_add_test( pSuite, "testInitXStrobePattern()", testInitXStrobePattern );
    CU_add_test( pSuite, "testInitUpperLowerPattern()", testInitUpperLowerPattern );
    CU_add_test( pSuite, "testInitLowerPattern()", testInitLowerPattern );
    CU_add_test( pSuite, "testInitPatternSelector()", testInitPatternSelector );
    CU_add_test( pSuite, "testNextPattern()", testNextPattern );

    return 0;
}

void FlushStageStash( void )
{
    stage_list_iter = 0;
    while( NewStage() != NULL )
        ;
    stage_list_iter = 0;
}

void FlushPatternStash( void )
{
    pattern_list_iter = 0;
    while( NewPattern() != NULL )
        ;
    pattern_list_iter = 0;
}

struct Stage* CopyStage( struct Stage* dest, struct Stage* source )
{
    CopyStageData( dest, source );
    dest->next = source->next;
    return dest;
}

struct Stage* GetStage( struct Stage* head, uint num )
{
    struct Stage* get_stage = head;
    for( int i = 1; i < num; i++ )
        get_stage = get_stage->next;

    return get_stage;
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

void ComparePatternWigwag( const struct Pattern* wigwag )
{
    CU_ASSERT( wigwag->name == WIGWAG );

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

void testInitWigwagPattern( void )
{
    FlushStageStash();
    struct Pattern* wigwag = NewPattern();
    InitWigwagPattern( wigwag );

    ComparePatternWigwag( wigwag );
}

void ComparePatternXStrobe( const struct Pattern* xstrobe )
{
    CU_ASSERT( xstrobe->name == XSTROBE );

    bool diag_1_4_states[NUM_LIGHTS] = { ON, OFF, OFF, ON };
    struct Stage* diag_1_4 = ConstructStage( diag_1_4_states, DEFAULT_INTERVAL, NULL );
    bool diag_2_3_states[NUM_LIGHTS] = { OFF, ON, ON, OFF };
    struct Stage* diag_2_3 = ConstructStage( diag_2_3_states, DEFAULT_INTERVAL, NULL );
    struct Stage* off = NewStage();

    CompareStageData( GetStage( xstrobe->first_stage, 1  ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 2  ), diag_1_4 );
    CompareStageData( GetStage( xstrobe->first_stage, 3  ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 4  ), diag_1_4 );
    CompareStageData( GetStage( xstrobe->first_stage, 5  ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 6  ), diag_1_4 );
    CompareStageData( GetStage( xstrobe->first_stage, 7  ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 8  ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 9  ), diag_2_3 );
    CompareStageData( GetStage( xstrobe->first_stage, 10 ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 11 ), diag_2_3 );
    CompareStageData( GetStage( xstrobe->first_stage, 12 ), off );
    CompareStageData( GetStage( xstrobe->first_stage, 13 ), diag_2_3 );
    CompareStageData( GetStage( xstrobe->first_stage, 14 ), off );
    CU_ASSERT_PTR_EQUAL( GetStage( xstrobe->first_stage, 14 )->next, xstrobe->first_stage );

    struct Stage* current_stage = xstrobe->first_stage;
    int i = 1;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, diag_1_4 );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, diag_1_4 );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, diag_1_4 );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, diag_2_3 );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, diag_2_3 );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, diag_2_3 );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( xstrobe->first_stage, i++ ) );
    current_stage = current_stage->next;
    CU_ASSERT_PTR_EQUAL( current_stage, xstrobe->first_stage );
}

void testInitXStrobePattern( void )
{
    FlushStageStash();
    struct Pattern* xstrobe = NewPattern();
    InitXStrobePattern( xstrobe );

    ComparePatternXStrobe( xstrobe );
}

void ComparePatternUpperLower( const struct Pattern* upper_lower )
{
    CU_ASSERT( upper_lower->name == UPPER_LOWER );

    bool upper_states[NUM_LIGHTS] = { ON, ON, OFF, OFF };
    struct Stage* upper = ConstructStage( upper_states, DEFAULT_INTERVAL, NULL );
    bool lower_states[NUM_LIGHTS] = { OFF, OFF, ON, ON };
    struct Stage* lower = ConstructStage( lower_states, DEFAULT_INTERVAL, NULL );
    struct Stage* off = NewStage();

    CompareStageData( GetStage( upper_lower->first_stage, 1  ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 2  ), upper );
    CompareStageData( GetStage( upper_lower->first_stage, 3  ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 4  ), upper );
    CompareStageData( GetStage( upper_lower->first_stage, 5  ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 6  ), upper );
    CompareStageData( GetStage( upper_lower->first_stage, 7  ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 8  ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 9  ), lower );
    CompareStageData( GetStage( upper_lower->first_stage, 10 ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 11 ), lower );
    CompareStageData( GetStage( upper_lower->first_stage, 12 ), off );
    CompareStageData( GetStage( upper_lower->first_stage, 13 ), lower );
    CompareStageData( GetStage( upper_lower->first_stage, 14 ), off );
    CU_ASSERT_PTR_EQUAL( GetStage( upper_lower->first_stage, 14 )->next, upper_lower->first_stage );

    struct Stage* current_stage = upper_lower->first_stage;
    int i = 1;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, upper );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, upper );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, upper );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( upper_lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CU_ASSERT_PTR_EQUAL( current_stage, upper_lower->first_stage );
}

void testInitUpperLowerPattern( void )
{
    FlushStageStash();
    struct Pattern* upper_lower = NewPattern();
    InitUpperLowerPattern( upper_lower );

    ComparePatternUpperLower( upper_lower );
}

void ComparePatternLower( const struct Pattern* lower )
{
    CU_ASSERT( lower->name == LOWER );

    bool lower_left_states[NUM_LIGHTS] = { OFF, OFF, ON, OFF };
    struct Stage* lower_left = ConstructStage( lower_left_states, DEFAULT_INTERVAL, NULL );
    bool lower_states[NUM_LIGHTS] = { OFF, OFF, OFF, ON };
    struct Stage* lower_right = ConstructStage( lower_states, DEFAULT_INTERVAL, NULL );
    struct Stage* off = NewStage();

    CompareStageData( GetStage( lower->first_stage, 1  ), off );
    CompareStageData( GetStage( lower->first_stage, 2  ), lower_left );
    CompareStageData( GetStage( lower->first_stage, 3  ), off );
    CompareStageData( GetStage( lower->first_stage, 4  ), lower_left );
    CompareStageData( GetStage( lower->first_stage, 5  ), off );
    CompareStageData( GetStage( lower->first_stage, 6  ), lower_left );
    CompareStageData( GetStage( lower->first_stage, 7  ), off );
    CompareStageData( GetStage( lower->first_stage, 8  ), off );
    CompareStageData( GetStage( lower->first_stage, 9  ), lower_right );
    CompareStageData( GetStage( lower->first_stage, 10 ), off );
    CompareStageData( GetStage( lower->first_stage, 11 ), lower_right );
    CompareStageData( GetStage( lower->first_stage, 12 ), off );
    CompareStageData( GetStage( lower->first_stage, 13 ), lower_right );
    CompareStageData( GetStage( lower->first_stage, 14 ), off );
    CU_ASSERT_PTR_EQUAL( GetStage( lower->first_stage, 14 )->next, lower->first_stage );

    struct Stage* current_stage = lower->first_stage;
    int i = 1;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower_left );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower_left );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower_left );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower_right );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower_right );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, lower_right );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CompareStageData( current_stage, off );
    CU_ASSERT_PTR_EQUAL( current_stage, GetStage( lower->first_stage, i++ ) );
    current_stage = current_stage->next;
    CU_ASSERT_PTR_EQUAL( current_stage, lower->first_stage );
}

void testInitLowerPattern( void )
{
    FlushStageStash();
    struct Pattern* lower = NewPattern();
    InitLowerPattern( lower );

    ComparePatternLower( lower );
}

void testInitPatternSelector( void )
{
    FlushPatternStash();
    FlushStageStash();
    struct PatternSelector p;
    InitPatternSelector( &p );

    struct Pattern* wigwag = p.patterns[WIGWAG];
    CU_ASSERT( wigwag->name == WIGWAG );

    bool left_side_states[NUM_LIGHTS] = { ON, OFF, ON, OFF };
    struct Stage* left_side_on = ConstructStage( left_side_states, DEFAULT_INTERVAL, NULL );
    bool right_side_states[NUM_LIGHTS] = { OFF, ON, OFF, ON };
    struct Stage* right_side_on = ConstructStage( right_side_states, DEFAULT_INTERVAL, NULL );
    struct Stage* off = NewStage();

    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, left_side_on );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, left_side_on );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, left_side_on );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, right_side_on );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, right_side_on );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, right_side_on );
    p.current_stage = p.current_stage->next;
    CompareStageData( p.current_stage, off );
    p.current_stage = p.current_stage->next;
    CU_ASSERT_PTR_EQUAL( p.current_stage, wigwag->first_stage );
}

void testNextPattern( void )
{

}