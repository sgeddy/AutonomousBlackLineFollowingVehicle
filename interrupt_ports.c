//------------------------------------------------------------------------------
//  Description: This file contains the interrupt instructions relating to the
//  ports in the device. 
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern char *display_1;
extern char *display_2;
volatile char switch_char;
extern volatile unsigned int SW1_PRESSED;
extern volatile unsigned int SW2_PRESSED;
extern volatile unsigned int SW1_DEBOUNCED;
extern volatile unsigned int SW2_DEBOUNCED;
extern volatile unsigned int SW1_DEBOUNCE_COUNT;
extern volatile unsigned int SW2_DEBOUNCE_COUNT;

#pragma vector=PORT4_VECTOR
__interrupt void switch_interrupt(void) {
//===========================================================================
// Function name: switch_interrupt
//
// Description: This is function that interupts the CPU to take action when
// switches are pressed.
//
// Passed : no variables passed
// Locals: no locals declared
// Returned: no values returned
// Globals: display_1, display_2, SW1_PRESSED, SW2_PRESSED, SW1_DEBOUNCE_COUNT
//          SW2_DEBOUNCE_COUNT, SW1_DEBOUNCED, SW2_DEBOUNCED
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
// Switch 1
 if (P4IFG & SW1) {
   TA0CCTL1 |= CCIE;
   TA1CCTL0 |= CCIE;
// Turn LED 3 on to indicate boot ISR working
   PJOUT |= LED4;
// Set a variable to identify the switch has been pressed.
   SW1_PRESSED = TRUE;
// Set a variable to identify the switch is being debounced.
   SW1_DEBOUNCED = TRUE;
// Reset the count required of the debounce.
   SW1_DEBOUNCE_COUNT = INIT;
// Disable the Switch Interrupt.
   P4IE &= ~SW1;
// Clear any current timer interrupt.
   P4IFG &= ~SW1;
   switch_char |= SW1;
   display_2 = "   Initiate  ";
 }
// Switch 2
 if (P4IFG & SW2) {
   TA0CCTL1 &= ~CCIE;
   TA1CCTL0 &= ~CCIE;
// Turn LED 4 on to indicate boot ISR working
   PJOUT |= LED4;
   wheels_off();
// Set a variable to identify the switch has been pressed.
   SW2_PRESSED = TRUE;
// Set a variable to identify the switch is being debounced.
   SW2_DEBOUNCED = TRUE;
// Reset the count required of the debounce.
   SW2_DEBOUNCE_COUNT = INIT;
// Disable the Switch Interrupt.
   P4IE &= ~SW2;
// Clear any current timer interrupt.
   P4IFG &= ~SW2;
   switch_char |= SW2;
   display_2 = "     Stop   ";
 }
// Enable the Timer Interrupt for the debounce.
}
