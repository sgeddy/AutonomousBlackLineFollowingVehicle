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

 //------------------------------------------------------------------------------
// Port J Pins
// Init_Port3
// Purpose: Initialize Port J
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - Analog input A12 ? ADC, Comparator_D input CD12, Vref- External applied reference
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - Analog input A13 ? ADC, Comparator_D input CD13, Input for an external reference voltage to the ADC
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - Analog input A14 - ADC, Comparator_D input CD14
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - Analog input A15 - ADC, Comparator_D input CD15
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
void Init_PortJ(char clock_state){
  if (clock_state==USE_R_FORWARD) {
    // Set Selections bits
    PJSEL0 = CLEAR_REGISTER;    // PJ set as I/0
    PJSEL1 = CLEAR_REGISTER;    // PJ set as I/0
    PJSEL0 &= ~LED1;
    PJSEL1 &= ~LED1;
    PJSEL0 &= ~LED2;
    PJSEL1 &= ~LED2;
    PJSEL0 &= ~LED3;
    PJSEL1 &= ~LED3;
    PJSEL0 &= ~LED4;
    PJSEL1 &= ~LED4;

    //Initialize outputs
    PJOUT &= ~LED1;
    PJOUT &= ~LED2;
    PJOUT &= ~LED3;
    PJOUT &= ~LED4;

    //Set pin directions
    PJDIR = OUTPUT_SET;         // Set PJ direction to output
    PJDIR |= LED1;
    PJDIR |= LED2;
    PJDIR |= LED3;
    PJDIR |= LED4;
  }
  if (clock_state==USE_SMCLK) {
    P3SEL0 = FUNCTION_REGISTER; // set default as SMCLK
    P3SEL1 = FUNCTION_REGISTER;
    P3DIR |= clock_state;
  }
}
