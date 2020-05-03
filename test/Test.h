#ifndef TEST_H
#define TEST_H

#include <CUnit/Basic.h>

#include "Pattern.h"

// testing helper functions
void FlushStageStash( void );
void CompareStage( const struct Stage* stage1, const struct Stage* stage2 );

int setupPatternTestSuite(void);

int initPatternTestSuite(void);
int cleanPatternTestSuite(void);

void testNewStageOverflow( void );
void testStageInitialization( void );
void testStageConstruction( void );
void testCopyStage( void );
void testAppendStage( void );

#endif
