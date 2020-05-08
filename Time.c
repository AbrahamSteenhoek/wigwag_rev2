#include "Time.h"

uint temp_ms = 0;

volatile unsigned long cur_ms = 0;

ulong ms()
{ 
    return cur_ms;
}
