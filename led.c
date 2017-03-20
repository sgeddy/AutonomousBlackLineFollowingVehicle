//------------------------------------------------------------------------------
//  Description: This file contains the LED routine
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_LEDs(void){
//===========================================================================
// Function name: Init_LEDs
//
// Description: This function ensures all LEDs are initiallized to be off.
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
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
  PJOUT &= ~LED4;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;
}
