#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include "mcc_generated_files/pin_manager.h"
#include "Types.h"

// setters for L
#define SET( pin, state )       do { pin = state; } while(0)

void SetLight( const enum Light light, const bool state );
void SetOutputs( const bool state );

#endif

