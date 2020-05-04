#ifndef TEST_H
#define TEST_H

#include <CUnit/Basic.h>

#include "Pattern.h"

// testing helper functions
void FlushStageStash( void );
void CompareStage( const struct Stage* stage1, const struct Stage* stage2 );
void CompareStageData( const struct Stage* stage1, const struct Stage* stage2 );
void StagesAreSame( const struct Stage* stage1, const struct Stage* stage2 );
struct Stage* GetStage( struct Stage* head, uint num );

int setupPatternTestSuite(void);

int initPatternTestSuite(void);
int cleanPatternTestSuite(void);

void testNewStageOverflow( void );
void testStageInitialization( void );
void testStageConstruction( void );
void testCopyStage( void );
void testAppendStage( void );
void testInitWigwagPattern( void );

#endif
