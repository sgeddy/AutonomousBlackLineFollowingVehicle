//------------------------------------------------------------------------------
//  Description: This file contains the black line detection algorithm.
//
//  Samuel Eddy
//  April 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern int ADC_Right_Detector;
extern int ADC_Left_Detector;
extern int sw2state;
extern unsigned int counter;

void blklinenav(void){
  sw2state = RESET;
  PJOUT &= ~R_FORWARD;
  PJOUT &= ~R_REVERSE;
  PJOUT &= ~L_FORWARD;
  PJOUT &= ~L_REVERSE;
  P1OUT |= IR_LED;
  counter = RESET;
  while(ALWAYS){
    if(counter > 10500) turnaround();
    PJOUT |= R_FORWARD;
    PJOUT |= L_FORWARD;
    ADC_Process();
    disp_Detector();
    if(ADC_Right_Detector < OFFR) turnleft();
    if(ADC_Left_Detector < OFFL) turnright();
  }
}

void turnright(void){
  while(ADC_Left_Detector < OFFL){
    ADC_Process();
    disp_Detector();
    PJOUT &= ~R_FORWARD;
    PJOUT &= ~L_FORWARD;
    usleep10(USLEEP1);
    if(ADC_Right_Detector < OFFR) hardright();
    PJOUT |= L_FORWARD;
    usleep10(USLEEP2);
    PJOUT &= ~L_FORWARD;
    usleep10(USLEEP1);
  }
}

void turnleft(void){
  while(ADC_Right_Detector < OFFR){
    ADC_Process();
    disp_Detector();
    PJOUT &= ~R_FORWARD;
    PJOUT &= ~L_FORWARD;
    usleep10(USLEEP1);
    if(ADC_Left_Detector < OFFL) hardleft();
    PJOUT |= R_FORWARD;
    usleep10(USLEEP2);
    PJOUT &= ~R_FORWARD;
    usleep10(USLEEP1);
  }
}
  
void hardright(void){
  while(ADC_Right_Detector < OFFR && ADC_Left_Detector < OFFL){
    ADC_Process();
    disp_Detector();
    PJOUT |= R_FORWARD;
    PJOUT &= ~L_FORWARD;
    usleep10(USLEEP2);
    PJOUT &= ~R_FORWARD;
  }
}

void hardleft(void){
  while(ADC_Right_Detector < OFFR && ADC_Left_Detector < OFFL){
    ADC_Process();
    disp_Detector();
    PJOUT |= L_FORWARD;
    PJOUT &= ~R_FORWARD;
    usleep10(USLEEP2);
    PJOUT &= ~L_FORWARD;
  }
}

void turnaround(void){
  ADC_Process();
  disp_Detector();
  PJOUT &= ~R_FORWARD;
  PJOUT &= ~R_REVERSE;
  PJOUT &= ~L_FORWARD;
  PJOUT &= ~L_REVERSE;
  PJOUT |= L_FORWARD;
  PJOUT |= R_REVERSE;
  five_msec_sleep(50);
  PJOUT &= ~L_FORWARD;
  PJOUT &= ~R_REVERSE;
  blklinenav();
}

void disp_Detector(void){
  char *display_Left = "Lft:            ";
  char *display_Right = "Rt:             ";
  *(display_Left+SIX) = (((ADC_Left_Detector/SHIFTTHREE)%MASK)|ASCIICONV);
  *(display_Left+SEVEN) = (((ADC_Left_Detector/SHIFTTWO)%MASK)|ASCIICONV);
  *(display_Left+EIGHT) = (((ADC_Left_Detector/SHIFTONE)%MASK)|ASCIICONV);
  *(display_Left+NINE) = ((ADC_Left_Detector%MASK)|ASCIICONV);
  lcd_out(display_Left,LCD_LINE_1);
  *(display_Right+SIX) = (((ADC_Right_Detector/SHIFTTHREE)%MASK)|ASCIICONV);
  *(display_Right+SEVEN) = (((ADC_Right_Detector/SHIFTTWO)%MASK)|ASCIICONV);
  *(display_Right+EIGHT) = (((ADC_Right_Detector/SHIFTONE)%MASK)|ASCIICONV);
  *(display_Right+NINE) = ((ADC_Right_Detector%MASK)|ASCIICONV);
  lcd_out(display_Right,LCD_LINE_2);
}
