//------------------------------------------------------------------------------
//  Description: This file contains the interrupt instructions for timers that 
//  are dependent on interrupts in other parts of the code.
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

unsigned int timerCount = INIT;
unsigned int count_up;
volatile char switch_flag;
extern volatile char switch_char;
extern volatile unsigned int SW1_PRESSED;
extern volatile unsigned int SW2_PRESSED;
extern volatile unsigned int SW1_DEBOUNCED;
extern volatile unsigned int SW2_DEBOUNCED;
extern volatile unsigned int SW1_DEBOUNCE_COUNT;
extern volatile unsigned int SW2_DEBOUNCE_COUNT;
extern volatile unsigned int DRIVING_FORWARD;
extern volatile unsigned int DRIVING_BACKWARD;
volatile unsigned int FIFTY_MSEC_TIMER = INIT;
volatile unsigned int ONE_SEC_COUNTER = INIT;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void){                                               // 50ms timer
//===========================================================================
// Function name: Timer0_A0
//
// Description: This interrupts the CPU to take action every
// interval of 50ms.
//
// Passed : no variables passed
// Locals: switch_flag, FIFTY_MSEC_TIMER
// Returned: no values returned
// Globals: display_1, display_2, SW1_PRESSED, SW2_PRESSED, SW1_DEBOUNCE_COUNT
//          SW2_DEBOUNCE_COUNT, SW1_DEBOUNCED, SW2_DEBOUNCED
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
  FIFTY_MSEC_TIMER++;
  count_up ++;
  if(count_up == DECADE) {
    P3DIR ^= LCD_BACKLITE;
    count_up = INIT;
  }
  TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void){                                               // 5ms timer
//===========================================================================
// Function name: Timer0_A1
//
// Description: This interrupts the CPU to take action every
// interval of 5ms.
//
// Passed : no variables passed
// Locals: switch_flag, FIFTY_MSEC_TIMER
// Returned: no values returned
// Globals: display_1, display_2, SW1_PRESSED, SW2_PRESSED, SW1_DEBOUNCE_COUNT
//          SW2_DEBOUNCE_COUNT, SW1_DEBOUNCED, SW2_DEBOUNCED
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
  switch(__even_in_range(TA0IV,14)){
  case 0: break; // No interrupt
  case 2: // CCR1 not used
      // Put code here for CCR1
      if(SW1_DEBOUNCED)
          SW1_DEBOUNCE_COUNT++;
      if(SW2_DEBOUNCED)
          SW2_DEBOUNCE_COUNT++;
//      if(DRIVING_FORWARD) {
//          right_wheel_off();
//          //usleep10(20);
//          left_wheel_off();
//          drive_forward();
//      }
//      if(DRIVING_BACKWARD) {
//          right_wheel_off();
//          //usleep10(20);
//          left_wheel_off();
//          drive_reverse();
//      }
      if(SW2_PRESSED)
          wheels_off();
      TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
  break;
  case 4: // CCR2 not used
      // Put code here for CCR2
      // TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
  break;
  case 6: break; // reserved
  case 8: break; // reserved
  case 10: break; // reserved
  case 12: break; // reserved
  case 14: // overflow
      // Put code here for overflow
  break;
  default: break;
  }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void){                                               // 1sec timer
//===========================================================================
// Function name: Timer1_A0
//
// Description: This interrupts the CPU to take action every
// interval of 1sec.
//
// Passed : no variables passed
// Locals: ONE_SEC_COUNTER
// Returned: no values returned
// Globals: display_1, display_2, SW1_PRESSED, SW2_PRESSED, SW1_DEBOUNCE_COUNT
//          SW2_DEBOUNCE_COUNT, SW1_DEBOUNCED, SW2_DEBOUNCED
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
  switch(ONE_SEC_COUNTER) {
  case 0: // Do nothing
      PJOUT |= LED2;
      break;
  case 1: // Do nothing
      PJOUT |= LED3;
      break;
  case 2: // Do nothing
      PJOUT |= LED4;
      break;
  case 3: // Do nothing
      P3OUT |= LED5;
      break;
  case 4: // Drive forward for 1 second
      P3OUT |= LED6;
      wheels_off();
      drive_forward();
      break;
  case 5: // Drive backward for 2 seconds
      P3OUT |= LED6;
      wheels_off();
      drive_reverse();
      break;
  case 6: // Drive backward for 2 seconds
      P3OUT |= LED6;
      wheels_off();
      drive_reverse();
      break;
  case 7: // Drive forward for 1 second
      P3OUT |= LED6;
      wheels_off();
      drive_forward();
      break;
  case 8: // Spin clockwise for 1 second
      P3OUT |= LED6;
      wheels_off();
      left_wheel_fwd();
      right_wheel_rev();
      break;
  case 9: // Spin counterclockwise for 1 second
      P3OUT |= LED6;
      wheels_off();
      right_wheel_fwd();
      left_wheel_rev();
      ONE_SEC_COUNTER = INIT;
      break;
  default: 
      ONE_SEC_COUNTER = INIT;
      break;
  }
  ONE_SEC_COUNTER++;
  TA1CCR0 += TA1CCR0_INTERVAL; // Add Offset to TACCR0
}
