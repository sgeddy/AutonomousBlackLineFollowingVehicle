//------------------------------------------------------------------------------
//  Description: This file contains the routine for Port 3
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//===========================================================================
// Init_Port3
// Purpose: Initialize Port 3
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
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR1 capture: CCI1B input
// 0 1 1 - TB1 CCR1 compare: Out1
// 1 1 X - TB2 clock input, SMCLK output
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR2 capture: CCI2B input
// 0 1 1 - TB1 CCR2 compare: Out2
// 1 1 X - Comparator_D output
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2 CCR1 capture: CCI1B input
// 0 1 1 - TB2 CCR1 compare: Out1
// 1 1 1 - TB1 clock input
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2 CCR2 capture: CCI2B input
// 0 1 1 - TB2 CCR2 compare: Out2 (not available on devices without TB2)
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
void Init_Port3(void){
  // Set Selections bits
  P3SEL0 = CLEAR_REGISTER; // P1 set default as I/0
  P3SEL1 = CLEAR_REGISTER; // P1 set default as I/0
  P3SELC &= ~LCD_BACKLITE;
  P3SEL0 &= ~LED5;
  P3SEL1 &= ~LED5;
  P3SEL0 &= ~LED6;
  P3SEL1 &= ~LED6;
  P3SEL0 &= ~LED7;
  P3SEL1 &= ~LED7;
  P3SEL0 &= ~LED8;
  P3SEL1 &= ~LED8;

  //Initialize outputs
  P3DIR |= LCD_BACKLITE;
  P3OUT = LCD_BACKLITE;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;

  //Set pin directions
  P3DIR |= LED5;         // Set P3 direction to output
  P3DIR |= LED6;         // Set P3 direction to output
  P3DIR |= LED7;         // Set P3 direction to output
  P3DIR |= LED8;         // Set P3 direction to output
}
