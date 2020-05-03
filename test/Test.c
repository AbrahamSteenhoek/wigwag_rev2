#include "Test.h"

void FlushStageStash( void )
{
    stage_list_iter = 0;
    while( NewStage() != NULL )
        ;
    stage_list_iter = 0;
}

void CompareStage( const struct Stage* stage1, const struct Stage* stage2 )
{
    for( int i = 0; i < NUM_LIGHTS; i++ )
        CU_ASSERT( stage1->light_states[i] == stage2->light_states[i] );
    CU_ASSERT( stage1->time_ms == stage2->time_ms );
    CU_ASSERT_PTR_EQUAL( stage1->next, stage2->next );
}

void StagesAreSame( const struct Stage* stage1, const struct Stage* stage2 )
{
    CU_ASSERT_PTR_EQUAL( stage1, stage2 );
    CompareStage( stage1, stage2 );
}

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

    return 0;
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
}