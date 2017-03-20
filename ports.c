//------------------------------------------------------------------------------
//  Description: This file contains the Ports routines
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Ports(void) {
//===========================================================================
// Function name: Init_Ports
//
// Description: This function calls all other port intitialization functions.
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
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ(USE_R_FORWARD);
}
