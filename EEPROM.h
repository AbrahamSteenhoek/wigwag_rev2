#ifndef EEPROM_H
#define	EEPROM_H

#include "Pattern.h"
#include "Types.h"

//#include <p16f18325.h>
#include <xc.h> // include processor files - each processor file is guarded.  

#define PATTERN_SAVE_ADDRESS    0

void EEPROM_SavePattern( enum PatternName pattern_name );

enum PatternName EEPROM_GetSavedPattern();

#endif
