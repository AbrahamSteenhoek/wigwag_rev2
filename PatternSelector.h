#ifndef PATTERNSELECTOR_H
#define	PATTERNSELECTOR_H

#include "Pattern.h"

struct PatternSelector {
    struct Pattern* patterns[ MAX_PATTERNS ];
    struct Stage* current_stage;
};

struct PatternSelector pattern_selector;

void InitPatternSelector( struct PatternSelector* p_selector );

#endif
