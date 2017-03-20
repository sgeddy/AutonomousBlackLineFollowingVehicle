//------------------------------------------------------------------------------
//  Description: This file contains the Timers routines
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

// Global Variables
extern volatile unsigned char control_state[CNTL_STATE_INDEX];
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern volatile unsigned int FIFTY_MSEC_TIMER;

void Init_Timers(void){
//===========================================================================
// Function name: Init_Timers
//
// Description: This function initializes the timers held in the timersB2.r43
// file.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no globals used
// 
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

  Init_Timer_A0(); //
  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
  Init_Timer_B2();   //  Required for provided compiled code to work
}

void usleep10(unsigned int usec){
//===========================================================================
// Function name: usleep10
//
// Description: This function forces the processor to sleep (perform counting)
// for a certain duration (in microseconds).
//
// At the current clock rate this yields about 10usec per value passed
// A value of  0 yields 1.37 uSec
// A value of  1 yields 1.87 uSec
// A value of  2 yields 2.36 uSec
// A value of  3 yields 2.86 uSec
// A value of  4 yields 3.36 uSec
// A value of  5 yields 3.86 uSec
// A value of  6 yields 4.36 uSec
// A value of  7 yields 4.85 uSec
// A value of  8 yields 5.354 uSec
// A value of  9 yields 5.854 uSec
// A value of 10 yields 6.353 uSec
// A value of 11 yields 6.851 uSec
// A value of 12 yields 7.351 uSec
// A value of 13 yields 7.849 uSec
// A value of 14 yields 8.350 uSec
// A value of 15 yields 8.849 uSec
// A value of 16 yields 9.342 uSec
// A value of 17 yields 9.84 uSec
// A value of 18 yields 10.34 uSec
// A value of 19 yields 10.84 uSec
//
// Passed : unsigned int usec
// Locals: int i, int j
// Returned: no globals used
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
  int i,j;
  for(j=INIT;j<usec;j++){
    for(i=INIT;i<USECDELAY;i++);
  }
}

void five_more_msec_mom(unsigned int fivemsec){
//===========================================================================
// Function name: five_more_msec_mom
//
// Description: This function forces the processor to sleep (perform counting)
// for a certain duration (in 5 millisecond intervals).
//
// Passed : unsigned int fivemsec
// Locals: no variables declared
// Returned: no values returned
// Globals: five_msec_count
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
//Each count passed is at least x times 5 milliseconds
  FIFTY_MSEC_TIMER = INIT;
  while(FIFTY_MSEC_TIMER < fivemsec);
}

void five_msec_sleep(unsigned int fivemsec){
//===========================================================================
// Function name: five_msec_sleep
//
// Description: This function forces the processor to sleep (perform counting)
// for a certain duration (in 5 millisecond intervals).
//
// Passed : unsigned int fivemsec
// Locals: no variables declared
// Returned: no values returned
// Globals: five_msec_count
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
//Each count passed is at least x times 5 milliseconds
  five_msec_count = INIT;
  while(fivemsec > (five_msec_count+INCREMENT));
}

void Init_Timer_A0(void) {
//===========================================================================
// Function name: Init_Timer_A0
//
// Description: This function contains the code to initialize Timer A0
// Timer A0 initialization sets up both A0_0 and A0_1-A0_2
//
// Passed : no variables passed
// Locals: one_time
// Returned: no values returned
// Globals: Time_Sequence, five_msec_count
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
 TA0CTL = TASSEL__SMCLK;        // SMCLK source
 TA0CTL |= TACLR;               // Resets TA0R, clock divider, count direction
 TA0CTL |= MC__CONTINUOUS;      // Continuous up
 TA0CTL |= ID__2;               // Divide clock by 2
 TA0CTL &= ~TAIE;               // Disable Overflow Interrupt
 TA0CTL &= ~TAIFG;              // Clear Overflow Interrupt flag

 TA0EX0 = TAIDEX_7;             // Divide clock by an additional 8

 TA0CCR0 = TA0CCR0_INTERVAL;    // CCR0
 TA0CCTL0 |= CCIE;              // CCR0 enable interrupt
 TA0CCR1 = TA0CCR1_INTERVAL;    // CCR1
// TA0CCR2 = TA0CCR2_INTERVAL;  // CCR2
// TA0CCTL2 |= CCIE;            // CCR2 enable interrupt
}

void Init_Timer_A1(void) {
//===========================================================================
// Function name: Init_Timer_A1
//
// Description: This function contains the code to initialize Timer A1
// Timer A0 initialization sets up both A1_0 and A1_1-A1_2
//
// Passed : no variables passed
// Locals: one_time
// Returned: no values returned
// Globals: Time_Sequence, five_msec_count
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
 TA1CTL = TASSEL__ACLK;         // ACLK source
 TA1CTL |= TACLR;               // Resets TA0R, clock divider, count direction
 TA1CTL |= MC__CONTINUOUS;      // Continuous up
 TA1CTL |= ID__1;               // Divide clock by 1
 TA1CTL &= ~TAIE;               // Disable Overflow Interrupt
 TA1CTL &= ~TAIFG;              // Clear Overflow Interrupt flag

 TA1EX0 = TAIDEX_7;             // Divide clock by an additional 8

 TA1CCR0 = TA1CCR0_INTERVAL;    // CCR0
// TA1CCR1 = TA1CCR1_INTERVAL;  // CCR1
// TA0CCR2 = TA0CCR2_INTERVAL;  // CCR2
// TA0CCTL2 |= CCIE;            // CCR2 enable interrupt
 
}


void TimerB0code(void){
//===========================================================================
// Function name: TimerB0code
//
// Description: This function contains the code to interrupt Timer B0
//
// Passed : no variables passed
// Locals: one_time
// Returned: no values returned
// Globals: Time_Sequence, five_msec_count
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
  Time_Sequence++;
  one_time = TRUE;
  if (five_msec_count < WTF_TOO_LARGE_DELAY){
    five_msec_count++;
  }
}
