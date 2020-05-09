#include "EEPROM.h"

void EEPROM_SavePattern( enum PatternName pattern_name )
{
    eeprom_write( PATTERN_SAVE_ADDRESS, (byte)pattern_name );
}

enum PatternName EEPROM_GetSavedPattern()
{
    enum PatternName saved_pattern = ( enum PatternName )eeprom_read( PATTERN_SAVE_ADDRESS );
    if ( saved_pattern != WIGWAG && saved_pattern != XSTROBE && saved_pattern != UPPER_LOWER && saved_pattern != LOWER )
        saved_pattern = WIGWAG;
    return saved_pattern;
}