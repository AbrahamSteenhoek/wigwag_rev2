#ifndef TEST_H
#define TEST_H

#include <CUnit/Basic.h>

#include "Pattern.h"
#include "PatternSelector.h"

// testing helper functions
void FlushStageStash( void );
void CompareStage( const struct Stage* stage1, const struct Stage* stage2 );
void CompareStageData( const struct Stage* stage1, const struct Stage* stage2 );
void StagesAreSame( const struct Stage* stage1, const struct Stage* stage2 );


int setupPatternTestSuite(void);

int initPatternTestSuite(void);
int cleanPatternTestSuite(void);

void testNewStageOverflow( void );
void testStageInitialization( void );
void testStageConstruction( void );
void testCopyStage( void );
void testAppendStage( void );
void testNewPattern( void );
void testInitWigwagPattern( void );
void testInitPatternSelector( void );

#endif
