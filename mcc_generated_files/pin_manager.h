/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F18325
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define TRUE    1
#define FALSE   0

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set turn_signal aliases
#define turn_signal_TRIS                 TRISCbits.TRISC0
#define turn_signal_LAT                  LATCbits.LATC0
#define turn_signal_PORT                 PORTCbits.RC0
#define turn_signal_WPU                  WPUCbits.WPUC0
#define turn_signal_OD                   ODCONCbits.ODCC0
#define turn_signal_ANS                  ANSELCbits.ANSC0
#define turn_signal_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define turn_signal_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define turn_signal_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define turn_signal_GetValue()           PORTCbits.RC0
#define turn_signal_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define turn_signal_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define turn_signal_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define turn_signal_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define turn_signal_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define turn_signal_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define turn_signal_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define turn_signal_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set L1 aliases
#define L1_TRIS                 TRISCbits.TRISC1
#define L1_LAT                  LATCbits.LATC1
#define L1_PORT                 PORTCbits.RC1
#define L1_WPU                  WPUCbits.WPUC1
#define L1_OD                   ODCONCbits.ODCC1
#define L1_ANS                  ANSELCbits.ANSC1
#define L1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define L1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define L1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define L1_GetValue()           PORTCbits.RC1
#define L1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define L1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define L1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define L1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define L1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define L1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define L1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define L1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set L2 aliases
#define L2_TRIS                 TRISCbits.TRISC2
#define L2_LAT                  LATCbits.LATC2
#define L2_PORT                 PORTCbits.RC2
#define L2_WPU                  WPUCbits.WPUC2
#define L2_OD                   ODCONCbits.ODCC2
#define L2_ANS                  ANSELCbits.ANSC2
#define L2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define L2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define L2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define L2_GetValue()           PORTCbits.RC2
#define L2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define L2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define L2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define L2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define L2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define L2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define L2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define L2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set L3 aliases
#define L3_TRIS                 TRISCbits.TRISC3
#define L3_LAT                  LATCbits.LATC3
#define L3_PORT                 PORTCbits.RC3
#define L3_WPU                  WPUCbits.WPUC3
#define L3_OD                   ODCONCbits.ODCC3
#define L3_ANS                  ANSELCbits.ANSC3
#define L3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define L3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define L3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define L3_GetValue()           PORTCbits.RC3
#define L3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define L3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define L3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define L3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define L3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define L3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define L3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define L3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set L4 aliases
#define L4_TRIS                 TRISCbits.TRISC4
#define L4_LAT                  LATCbits.LATC4
#define L4_PORT                 PORTCbits.RC4
#define L4_WPU                  WPUCbits.WPUC4
#define L4_OD                   ODCONCbits.ODCC4
#define L4_ANS                  ANSELCbits.ANSC4
#define L4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define L4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define L4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define L4_GetValue()           PORTCbits.RC4
#define L4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define L4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define L4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define L4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define L4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define L4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define L4_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define L4_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set pattern_cycle aliases
#define pattern_cycle_TRIS                 TRISCbits.TRISC5
#define pattern_cycle_LAT                  LATCbits.LATC5
#define pattern_cycle_PORT                 PORTCbits.RC5
#define pattern_cycle_WPU                  WPUCbits.WPUC5
#define pattern_cycle_OD                   ODCONCbits.ODCC5
#define pattern_cycle_ANS                  ANSELCbits.ANSC5
#define pattern_cycle_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define pattern_cycle_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define pattern_cycle_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define pattern_cycle_GetValue()           PORTCbits.RC5
#define pattern_cycle_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define pattern_cycle_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define pattern_cycle_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define pattern_cycle_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define pattern_cycle_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define pattern_cycle_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define pattern_cycle_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define pattern_cycle_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF0 pin functionality
 * @Example
    IOCCF0_ISR();
 */
void IOCCF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF0_SetInterruptHandler() method.
    This handler is called every time the IOCCF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(IOCCF0_InterruptHandler);

*/
extern void (*IOCCF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF0_SetInterruptHandler() method.
    This handler is called every time the IOCCF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(IOCCF0_DefaultInterruptHandler);

*/
void IOCCF0_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/