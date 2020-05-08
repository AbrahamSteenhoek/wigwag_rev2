#ifndef PATTERNFLASHER_H
#define	PATTERNFLASHER_H

#include "Lights.h"
#include "Pattern.h"
#include "PatternSelector.h"
#include "Types.h"

//struct Stage* current_stage;

bool update_stage = false;

uint start_time = 0;

void FlashPattern();

#endif