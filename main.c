//------------------------------------------------------------------------------
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Samuel Eddy
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
volatile char one_time;
volatile unsigned int five_msec_count;
volatile unsigned int SW1_PRESSED = FALSE;
volatile unsigned int SW2_PRESSED = FALSE;
volatile unsigned int SW1_DEBOUNCED = FALSE;
volatile unsigned int SW2_DEBOUNCED = FALSE;
volatile unsigned int SW1_DEBOUNCE_COUNT = INIT;
volatile unsigned int SW2_DEBOUNCE_COUNT = INIT;
extern char *display_1;
extern char *display_2;

char *display_NCSU;
char *display_P3;

//------------------------------------------------------------------------------

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
// 
//------------------------------------------------------------------------------
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  //PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Time_Sequence = INIT;                        // 
  Init_Timers();                            // Initialize Timers
  five_more_msec_mom(TWOHUNDREDFIFTY_MSEC_DELAY);                          // 250 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  five_more_msec_mom(THREEHUNDREDSEVENTYFIVE_MSEC_DELAY);                  // 375 msec delay for the clock to settle
  Init_LEDs();                              // Initialize LEDs
  display_NCSU = "   N.C. State   ";
  display_P3 =  "   Homework_06   ";
  display_2 = "";
  SW1_PRESSED = FALSE;                      // No switches have been pressed at start
  SW2_PRESSED = FALSE;
  
//  lcd_command(CLEAR_DISPLAY);
  five_more_msec_mom(TEN_CYCLES); 
  lcd_out(display_NCSU,LCD_LINE_1);       // 16 characters max between quotes - line 1
  lcd_out(display_P3,LCD_LINE_2);        // 16 characters max between quotes - line 2
    
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
// while(ALWAYS) {                            // Can the Operating system run
//  switch(Time_Sequence){
//    case TS_DAMN_DIS_IS_HUGE:                               // 1000 msec  
//      if(one_time){
//        Init_LEDs();                        // Initialize LEDs
//        one_time = INIT;
//      }
//      Time_Sequence = INIT;                    // 
//    case TS_PRETTY_BIG:                               // 1000 msec  
//      if(one_time){
//        PJOUT |= LED4;                      // Change State of LED 4
//        P3OUT |= LED5;                      // Change State of LED 5
//        one_time = INIT;
//      }
//    case TS_LARGE:                               // 750 msec  
//      if(one_time){
//        PJOUT |= LED3;                      // Change State of LED 3
//        P3OUT |= LED6;                      // Change State of LED 6
//        one_time = INIT;
//      }
//    case TS_MEDIUM:                               // 500 msec  
//      if(one_time){
//        PJOUT |= LED2;                      // Change State of LED 2
//        P3OUT |= LED7;                      // Change State of LED 7
//        one_time = INIT;
//      }
//    case  TS_KIND_OF_SMALL:                               // 250 msec  
//      if(one_time){
//        PJOUT |= LED1;                      // Change State of LED 1
//        P3OUT |= LED8;                      // Change State of LED 8
//        one_time = INIT;
//      }
//      break;
//    default: break; 
//  }
//  if(Time_Sequence > TS_DAMN_DIS_IS_HUGE){
//      Time_Sequence = INIT;
//  }
  while(ALWAYS) {
  Switches_Process();
  lcd_out(display_NCSU,LCD_LINE_1);
  lcd_out(display_2,LCD_LINE_2);
  }
}
