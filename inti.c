//------------------------------------------------------------------------------
//  Description: This file contains the Initial Conditions routine
//
//  Samuel Eddy
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Conditions(void){
//===========================================================================
// Function name: Init_LEDs
//
// Description: This function enalbes interrupts because they are disabled
// by default.
//
// Passed : no variables passed
// Locals: no locals declared
// Returned: no values returned
// Globals: no globals used
//
// Author: Samuel Eddy
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
  enable_interrupts();

//------------------------------------------------------------------------------
}
