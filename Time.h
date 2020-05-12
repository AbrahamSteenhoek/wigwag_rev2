/* 
 * File: Time.h
 * Author: Abraham Steenhoek
 * Comments: 
 * Revision history: 
 */

#ifndef TIME_H
#define	TIME_H

#include "Types.h"

/*
variable keeping track of the millisecond clock. DO NOT MODIFY.
*/
volatile ulong cur_ms;

/**
    <p><b>Function prototype: ulong ms() </b></p>
  
    <p><b>Summary: Getter function to read the clock that increments every millisecond </b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition: none </b></p>

    <p><b>Parameters: none </b></p>

    <p><b>Returns: ulong that represents the # of milliseconds passed since system startup </b></p>

    <p><b>Example:</b></p>
    <code>
        ulong delay_interval = 500;
        ulong time_mark = ms();
        while(1)
        {
            if ( ms() - time_mark > delay_interval )
            {
                break;
            }
        }
    </code>

    <p><b>Remarks: Future maintenance: introduce atomic read of the clock, also extract code incrementing time variable into custom subroutine. </b></p>
 */
ulong ms(); 

#endif

