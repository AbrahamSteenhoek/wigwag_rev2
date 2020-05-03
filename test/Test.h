#ifndef TEST_H
#define TEST_H

#include <CUnit/Basic.h>

#include "Pattern.h"

int setupPatternTestSuite(void);

void testPatternCreation( void );
int initPatternTestSuite(void);
int cleanPatternTestSuite(void);

#endif