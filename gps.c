//--------------------------------------------------------------------------- 
//  Description: This file contains all of the GPS functions.
// 
//  Jason Zicherman 
//  February 2015 
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include  "math.h"

extern volatile unsigned char GPS_Char_Rx[LARGE_RING_SIZE];
extern volatile unsigned char NEMA_BUF[LARGE_RING_SIZE];
extern volatile unsigned int gps_rx_ring_rd;
extern volatile unsigned int gps_rx_ring_wr;
extern unsigned int counter;
volatile unsigned char lattitude[NINE];
volatile char latdir;
volatile unsigned char longitude[TEN];
volatile char londir;
volatile unsigned int valid = FALSE;
extern int sw1state;
extern int sw2state;
double latnum;
double lonnum;
volatile double point1[TWO];
volatile double point2[TWO];
volatile double point3[TWO];
volatile double distance;
volatile int ptnum = RESET;
extern volatile unsigned int parsenow;
char distanceascii[EIGHT];

 
//--------------------------------------------------------------------------- 
// Function name: gps_system_init 
// 
// Description: This function initializes the gps.
// 
// Passed : no variables passed 
// Locals: no variables declared 
// Returned: no values returned 
// Globals: counter
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void gps_system_init(void){
  counter = RESET;
  P3OUT &= ~GPS_RESET;          // GPS_RESET = GPS in Reset;
  while (counter <= TWOHUN);
  counter = RESET;
  P3OUT |= GPS_RESET;           // GPS_RESET = GPS NOT Reset;
  while (counter <= TWOHUN);
  gps_wakeup();
  while(!(P3IN & GPS_PWRCHK)){
    if (!(P3IN & GPS_PWRCHK)){
      while (counter <= TWOHUNTEN);
      gps_wakeup();
    }
  }
}

//--------------------------------------------------------------------------- 
// Function name: gps_wakeup
// 
// Description: This function resets and powers on the GPS.
// 
// Passed : no variables passed 
// Locals: kick_out 
// Returned: no values returned 
// Globals: counter
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void gps_wakeup(void){
  int kick_out = INCREMENT;
  counter = RESET;
  while (counter <= TEN);
  P3OUT |= GPS_PWRCNTL;         // GPS_PWRCNTL = GPS_ON;
  counter = RESET;
  while ((counter <= TWENTY) & kick_out){
    if (P3IN & GPS_PWRCHK){
      kick_out = RESET;
    }
  }
  P3OUT &= ~GPS_PWRCNTL;        // GPS_PWRCNTL = GPS_Off;
}

//--------------------------------------------------------------------------- 
// Function name: gps_out_once
// 
// Description: This function resets and powers on the GPS.
// 
// Passed : no variables passed 
// Locals: jtemp1, jtemp2, display_line_1, display_line_2
// Returned: no values returned 
// Globals: no globals manipulated
//
/
 
/ Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void gps_out_once(void){
  unsigned int jtemp1;
  unsigned int jtemp2 = RESET;
  char display_line_1[SIXTEEN];
  char display_line_2[SIXTEEN];
  display_line_1[FIRST] = 'L';
  display_line_1[SECOND] = 'A';
  display_line_1[THIRD] = 'T';
  display_line_1[FOURTH] = ' ';
  display_line_1[FIFTH] = ' ';
  for(jtemp1 = SIXTH; jtemp1 < FOURTEEN; jtemp1++) display_line_1[jtemp1] = lattitude[jtemp2++];
  jtemp2 = RESET;
  display_line_1[FIFTEENTH] = ' ';
  display_line_1[SIXTEENTH] = latdir;
  display_line_2[FIRST] = 'L';
  display_line_2[SECOND] = 'O';
  display_line_2[THIRD] = 'N';
  display_line_2[FOURTH] = ' ';
  for(jtemp1 = FIFTH; jtemp1 < FOURTEEN; jtemp1++) display_line_2[jtemp1] = longitude[jtemp2++];
  display_line_2[FIFTEENTH] = ' ';
  display_line_2[SIXTEENTH] = londir;
  lcd_out(display_line_1,LCD_LINE_1);
  lcd_out(display_line_2,LCD_LINE_2);
  valid = FALSE;
}

//--------------------------------------------------------------------------- 
// Function name: parse
// 
// Description: This function processes the GPS data.
// 
// Passed : no variables passed 
// Locals: jtemp1, jtemp2
// Returned: no values returned 
// Globals: lattitude, latdir, longitude, londir
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void parse(void){
  unsigned int jtemp1;
  unsigned int jtemp2;
  if(NEMA_BUF[FIRST] == '$' && NEMA_BUF[SECOND] == 'G'){
    if(NEMA_BUF[FOURTH] == 'R' && NEMA_BUF[FIFTH] == 'M' && NEMA_BUF[SIXTH] == 'C'){
      if(NEMA_BUF[NINETEENTH] == 'A'){
        jtemp2 = RESET;
        for(jtemp1 = TWENTYFIRST; jtemp1 < TWENTYNINE; jtemp1++){
          if(NEMA_BUF[jtemp1] == ',') lattitude[jtemp2++] = ' ';
          else lattitude[jtemp2++] = NEMA_BUF[jtemp1];
        }
        latdir = NEMA_BUF[THIRTYFIRST];
        jtemp2 = RESET;
        for(jtemp1 = THIRTYTHIRD; jtemp1 < FOURTYTWO; jtemp1++){
          if(NEMA_BUF[jtemp1] == ',') longitude[jtemp2++] = ' ';
          else longitude[jtemp2++] = NEMA_BUF[jtemp1];
        }
        londir = NEMA_BUF[FOURTYFOURTH];
        valid = TRUE;
      }
     
 
 else{
        for(jtemp2 = FIRST; jtemp2 < NINE; jtemp2++) lattitude[jtemp2] = '?';
        latdir = '?';
        for(jtemp2 = FIRST; jtemp2 < TEN; jtemp2++) longitude[jtemp2] = '?';
        londir = '?';
        valid = TRUE;
      }
    }
  }
}

void asciitonum(void){
  double exponent = SHIFTTHREE;
  unsigned int jtemp;
  latnum = RESET;
  lonnum = RESET;
  if(parsenow == TRUE) parse();
  for(jtemp = RESET; jtemp < NINE; jtemp++){
    latnum += (lattitude[jtemp] - '0')*exponent;
    exponent /= SHIFTONE;
    if(jtemp == FOUR) jtemp++;
  }
  exponent = SHIFTFOUR;
  for(jtemp = RESET; jtemp < TEN; jtemp++){
    lonnum += (longitude[jtemp] - '0')*exponent;
    exponent /= SHIFTONE;
    if(jtemp == FIVE) jtemp++;
  }
}

void navigationinit(void){
  sw1state = RESET;
  ptnum = ONE;
  while(sw1state == RESET){
    lcd_out(" Press SW1 for  ",LCD_LINE_1);
    lcd_out("  first point   ",LCD_LINE_2);
    Switches_Process();
    if(sw1state == PRESSED){
      asciitonum();
      point1[FIRST] = latnum;
      point1[SECOND] = lonnum;
    }
  }
  sw1state = RESET;
  while(sw1state == RESET){
    lcd_out(" Press SW1 for  ",LCD_LINE_1);
    lcd_out("  second point  ",LCD_LINE_2);
    Switches_Process();
    if(sw1state == PRESSED){
      asciitonum();
      point2[FIRST] = latnum;
      point2[SECOND] = lonnum;
    }
  }
  sw1state = RESET;
  while(sw1state == RESET){
    lcd_out(" Press SW1 for  ",LCD_LINE_1);
    lcd_out("  third point   ",LCD_LINE_2);
    Switches_Process();
    if(sw1state == PRESSED){
      asciitonum();
      point3[FIRST] = latnum;
      point3[SECOND] = lonnum;
    }
  }
}

 
void distanceformula(void){
  double term1;
  double term2;
  asciitonum();
  if(ptnum == ONE){
    term1 = latnum;
    term1 -= point1[FIRST];
    term2 = lonnum;
    term2 -= point1[SECOND];
  }
  if(ptnum == TWO){
    term1 = latnum;
    term1 -= point2[FIRST];
    term2 = lonnum;
    term2 -= point2[SECOND];
  }
  if(ptnum == THREE){
    term1 = latnum;
    term1 -= point3[FIRST];
    term2 = lonnum;
    term2 -= point3[SECOND];
  }
  distance = LATLONTOM*sqrt(pow(term1,TWO)+pow(term2,TWO));
}

void anglecorrect(void){
  double samp1[TWO];
  double currentvec[TWO];
  double desiredvec[TWO];
  double angle;
  double numerator;
  double denominator;
  double delta;
  int waittime;
  asciitonum();
  samp1[FIRST] = latnum;
  samp1[SECOND] = lonnum;
  five_msec_delay(SHIFTTWO);
  asciitonum();
  currentvec[FIRST] = latnum - samp1[FIRST];
  currentvec[SECOND] = lonnum - samp1[SECOND];
  if(ptnum == ONE){
    desiredvec[FIRST] = point1[FIRST];
    desiredvec[FIRST] -= latnum;
    desiredvec[SECOND] = point1[SECOND];
    desiredvec[SECOND] -= lonnum;
  }
  else if(ptnum == TWO){
    desiredvec[FIRST] = point2[FIRST];
    desiredvec[FIRST] -= latnum;
    desiredvec[SECOND] = point2[SECOND];
    desiredvec[SECOND] -= lonnum;
  }
  else if(ptnum == THREE){
    desiredvec[FIRST] = point3[FIRST];
    desiredvec[FIRST] -= latnum;
    desiredvec[SECOND] = point3[SECOND];
    desiredvec[SECOND] -= lonnum;
  }
  
 
numerator = currentvec[FIRST]*desiredvec[FIRST]+currentvec[SECOND]*desiredvec[SECOND];
  denominator = sqrt(pow(currentvec[FIRST],TWO)+pow(currentvec[SECOND],TWO))+sqrt(pow(desiredvec[FIRST],TWO)+pow(desiredvec[SECOND],TWO));
  angle = numerator/denominator;
  if(angle < ZERO) angle = sqrt(pow(angle,TWO));
  angle *= RADTODEG;
  waittime = (int)angle;
  delta = currentvec[FIRST]*desiredvec[SECOND]-currentvec[SECOND]*desiredvec[FIRST];
  PJOUT &= ~R_FORWARD;
  PJOUT &= ~R_REVERSE;
  PJOUT &= ~L_FORWARD;
  PJOUT &= ~L_REVERSE;
  if(delta > ZERO){
    PJOUT |= R_FORWARD;
    PJOUT |= L_REVERSE;
    five_msec_delay(waittime);
    PJOUT &= R_FORWARD;
    PJOUT &= L_REVERSE;
  }
  if(delta < ZERO){
    PJOUT |= L_FORWARD;
    PJOUT |= R_REVERSE;
    five_msec_delay(waittime);
    PJOUT &= L_FORWARD;
    PJOUT &= R_REVERSE;
  }
  if(delta == ZERO){
    PJOUT |= L_FORWARD;
    PJOUT |= R_REVERSE;
    five_msec_delay(180);
    PJOUT &= L_FORWARD;
    PJOUT &= R_REVERSE;
  }
}

void navigation(void){
  sw2state = RESET;
  if(ptnum == FOUR) ptnum = ONE;
  while(ptnum <= THREE){
    while(ALWAYS){
      if(parsenow == TRUE) parse();
      PJOUT &= ~R_FORWARD;
      PJOUT &= ~R_REVERSE;
      PJOUT &= ~L_FORWARD;
      PJOUT &= ~L_REVERSE;
      PJOUT |= R_FORWARD;
      PJOUT |= L_FORWARD;
      five_msec_delay(TWOHUN);
      anglecorrect();
      distanceformula();
      //displaydistance();
      if(distance < TWO) break;
    }
    ptnum++;
  }
}

 
void displaydistance(void){
  int jtemp;
  double tempnum1;
  int tempnum2;
  double exponent = .01;
  while(ALWAYS){
    for(jtemp = RESET; jtemp < EIGHT; jtemp++){
      tempnum1 = distance*exponent;
      tempnum2 = (int)tempnum1;
      tempnum2 = tempnum2%10;
      tempnum2 += '0';
      distanceascii[jtemp] = tempnum2;
      exponent *= 10;
    }
    lcd_out("    Distance    ",LCD_LINE_1);
    lcd_out("                ",LCD_LINE_2);
    lcd_out(distanceascii,LCD_LINE_2);
  }
}
