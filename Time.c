

#include "Time.h"

volatile unsigned long cur_ms = 0;

/*
    <p><b>Function prototype: ulong ms() </b></p>
    See header file for usage info
*/
ulong ms()
{ 
    return cur_ms;
}
