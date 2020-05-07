#ifndef TEST_H
#define TEST_H

#include <CUnit/Basic.h>

#include "Pattern.h"
#include "PatternSelector.h"

// testing helper functions
void FlushStageStash( void );
void FlushPatternStash( void );
struct Stage* CopyStage( struct Stage* dest, struct Stage* source );
struct Stage* GetStage( struct Stage* head, uint num );
void CompareStage( const struct Stage* stage1, const struct Stage* stage2 );
void CompareStageData( const struct Stage* stage1, const struct Stage* stage2 );
void StagesAreSame( const struct Stage* stage1, const struct Stage* stage2 );

void ComparePatternWigwag( const struct Pattern* wigwag );
void ComparePatternXStrobe( const struct Pattern* xstrobe );
void ComparePatternUpperLower( const struct Pattern* upper_lower );
void ComparePatternLower( const struct Pattern* lower );

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
void testInitXStrobePattern( void );
void testInitUpperLowerPattern( void );
void testInitLowerPattern( void );
void testInitPatternSelector( void );
void testNextPattern( void );

#endif
