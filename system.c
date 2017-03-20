//------------------------------------------------------------------------------
//  Description: System Configurations
//  Tells the compiler to provide the value in reg as an input to an 
//  inline assembly block.  Even though the block contains no instructions,
//  the compiler may not optimize it away, and is told that the value
//  may change and should not be relied upon.
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//------------------------------------------------------------------------------

void enable_interrupts(void){
//===========================================================================
// Function name: enable_interrupts
//
// Description: This function contains the code enable interupts
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
  __bis_SR_register(GIE);     // enable interrupts
}
