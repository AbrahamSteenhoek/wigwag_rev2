#include "Test.h"

void testStageInitialization( void )
{
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
    struct Stage *stage = ConstructStage( temp_states, 100 );

    CU_ASSERT( stage->light_states[L1] == ON );
    CU_ASSERT( stage->light_states[L2] == OFF );
    CU_ASSERT( stage->light_states[L3] == ON );
    CU_ASSERT( stage->light_states[L4] == OFF );

    CU_ASSERT( stage->time_ms == 100 );
    CU_ASSERT_PTR_NULL( stage->next );
}

void testPatternCreation( void )
{

}

int initPatternTestSuite(void)
{
	return 0;
}

int cleanPatternTestSuite(void)
{
	return 0;
}

int setupPatternTestSuite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Pattern Test Suite", initPatternTestSuite, cleanPatternTestSuite);
	if (NULL == pSuite)
		return -1;
    CU_add_test( pSuite, "testStageInitialization()", testStageInitialization );
    CU_add_test( pSuite, "testStageConstruction()", testStageConstruction );
	CU_add_test( pSuite, "testPatternCreation()", testPatternCreation );


	return 0;
}