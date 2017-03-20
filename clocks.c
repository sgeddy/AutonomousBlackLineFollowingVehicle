//------------------------------------------------------------------------------
//  Description: This file contains the Clocks routine
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Clocks(void){
//===========================================================================
// Function name: Init_Clocks
//
// Description: This is the clock initialization for the program.
//
// Initial clock configuration, runs immediately after boot.
// Disables 1ms watchdog timer, 
//      configure MCLK to 8MHz
//      configure SMCLK to 8MHz.  
// Since the X1 oscillator is not currently connected, 
// X1CLK is an unknown speed (probably ~10kHz).
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
  WDTCTL = WDTPW | WDTHOLD;            // Disable watchdog
// Clocks:
  CSCTL0 = CSKEY;                      // Unlock register
  
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;       // Set max. DCO setting [8MHz]
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;   // set ACLK = vlo; SMCLK = DCO; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;   // set all dividers /1
  
  CSCTL0_H = CSLOCK;                   // Lock registers
}
