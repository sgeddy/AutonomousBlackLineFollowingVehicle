//------------------------------------------------------------------------------
//  Description: This file contains the routine for Port 4
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

 //----------------------------------------------------------------
// Configure PORT 4
//
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Tyler Cheek
// Date: Febrary 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
void Init_Port4(void){
//  P4SEL0 = INPUT_SET;         // P4 set as I/0
//  P4SEL1 = INPUT_SET;         // P4 set as I/0
//  P4DIR = CLEAR_REGISTER;     // Set P4 direction to input
//  P4DIR &= ~(SW1 | SW2);      // Direction = input
//  P4OUT = CLEAR_REGISTER;     // Clear the output register for P4
//  P4OUT |= SW1 | SW2;         // Configure pullup resistor
//  P4REN |= SW1 | SW2;         // Enable pullup resistor
  
    P4SEL0 = CLEAR_REGISTER;    // P4 set as I/0
    P4SEL1 = CLEAR_REGISTER;    // P4 set as I/0
    P4DIR = CLEAR_REGISTER;     // Set P4 direction to input
    P4DIR &= ~(SW1 | SW2);      // Direction = input
    P4OUT = CLEAR_REGISTER;
    P4OUT |= SW1;               // Configure pullup resistor
    P4OUT |= SW2;               // Configure pullup resistor
    P4REN |= SW1;               // Enable pullup resistor
    P4REN |= SW2;               // Enable pullup resistor
    // Configure the interrupt
    P4IES |= SW1;               // P4.0 Hi/Lo edge interrupt
    P4IES |= SW2;               // P4.0 Hi/Lo edge interrupt
    P4IFG &= ~SW1;              // P4 IFG SW1 cleared
    P4IFG &= ~SW2;              // P4 IFG SW2 cleared
    // Start/Enable Interrupt
    P4IE |= SW1;                // P4.0 SW1 interrupt Enabled
    P4IE |= SW2;                // P4.0 SW2 interrupt enabled
}
