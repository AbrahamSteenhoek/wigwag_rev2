/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PATTERN_H
#define	PATTERN_H

#include "Types.h"

#define DEFAULT_INTERVAL    60UL

enum { NUM_LIGHTS = 4 };
enum { MAX_STAGES = 96 };
enum { MAX_PATTERNS = MAX_STAGES/16 }; // each pattern uses at most 16 stages, so 6 patterns
enum PatternName{ WIGWAG = 0, XSTROBE = 1, UPPER_LOWER = 2, LOWER = 3, LAST = LOWER }; // for now, at most 6 patterns. (96/16=6);

struct Stage {
    bool light_states[ NUM_LIGHTS ];
    uint time_ms; // time in milliseconds
    struct Stage* next;
};

struct Pattern {
    enum PatternName name;
    struct Stage* first_stage; // points to the beginning of the stage list for this pattern
};

struct Stage stage_stash[ MAX_STAGES ];
uint stage_list_iter;

struct Pattern pattern_stash[ MAX_PATTERNS ];
uint pattern_list_iter;

struct Pattern* NewPattern();

void AssignLightStates( struct Stage* stage, const bool states[4] );

struct Stage* NewStage();

struct Stage* ConstructStage( const bool states[NUM_LIGHTS], const uint time_ms, struct Stage* next );

struct Stage* CopyStageData( struct Stage* dest, struct Stage* source );

void AppendStage( struct Stage* head, struct Stage* new_stage );

void InitWigwagPattern( struct Pattern* pattern );

void InitXStrobePattern( struct Pattern* pattern );

void InitUpperLowerPattern( struct Pattern* pattern );

void InitLowerPattern( struct Pattern* pattern );

#endif
