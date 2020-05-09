#ifndef PATTERNSELECTOR_H
#define	PATTERNSELECTOR_H

#include "EEPROM.h"
#include "Pattern.h"

struct PatternSelector {
    struct Pattern* patterns[ MAX_PATTERNS ];
    enum PatternName active;
    struct Stage* current_stage;
    volatile ulong start_time;
};

struct PatternSelector pattern_selector;

struct Pattern* ActivePattern( struct PatternSelector* p );

void InitPatternSelector( struct PatternSelector* p_selector );

struct Pattern* NextPattern( struct PatternSelector* p_selector );

#endif
