//------------------------------------------------------------------------------
//  Description: This file contains the Switch routine
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile unsigned int SW1_PRESSED;
extern volatile unsigned int SW2_PRESSED;
extern volatile unsigned int SW1_DEBOUNCED;
extern volatile unsigned int SW2_DEBOUNCED;
extern volatile unsigned int SW1_DEBOUNCE_COUNT;
extern volatile unsigned int SW2_DEBOUNCE_COUNT;

void Switches_Process(void) {
//===========================================================================
// Function name: switch_interrupt
//
// Description: This is function that interupts the CPU to take action when
// switches are pressed.
//
// Passed : no variables passed
// Locals: no locals declared
// Returned: no values returned
// Globals: no globals used
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
// Switch 1
 if(SW1_DEBOUNCE_COUNT >= DEBOUNCE_DELAY){
      P4IE |= SW1;
      SW1_DEBOUNCED = FALSE;
      SW1_PRESSED = FALSE;
 }
 if(SW2_DEBOUNCE_COUNT >= DEBOUNCE_DELAY) {
      P4IE |= SW2;
      SW2_DEBOUNCED = FALSE;
      SW2_PRESSED = FALSE;
 }
 if (!(SW1_DEBOUNCED) && !(SW2_DEBOUNCED)) {
      TA0CCTL1 &= ~CCIE;            // CCR1 enable interrupt
      PJOUT &= ~LED4;
 }
}
