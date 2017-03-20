//--------------------------------------------------------------------------- 
//  Description: This file contains the functions that handle serial
//  communications.
// 
//  Jason Zicherman 
//  February 2015 
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
char *USB_Char_Rx;
char *USB_Char_Tx;
unsigned int temp = RESET;
extern int sw2state;
int start = RESET;
int increment = RESET;
unsigned int temptx = RESET;
unsigned int firsttime = INCREMENT;
unsigned int i = RESET;
volatile unsigned char GPS_Char_Rx[LARGE_RING_SIZE];
volatile unsigned char NEMA_BUF[LARGE_RING_SIZE];
volatile unsigned int gps_rx_ring_rd = RESET;
volatile unsigned int gps_rx_ring_wr = RESET;
volatile unsigned int parsenow = RESET;

//--------------------------------------------------------------------------- 
// Function name: Init_Serial_UCA0
// 
// Description: This function initializes serial communications.
// 
// Passed : no variables passed 
// Locals: i
// Returned: no values returned 
// Globals: no values manipulated
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void Init_Serial_UCA1(void){
  USB_Char_Rx = "                ";     // USB Character
  USB_Char_Tx = "1     ";
  temp = RESET;
  usb_rx_ring_wr = RESET;
  usb_rx_ring_rd = RESET;
  // Configure UART 0
  UCA1CTLW0 = RESET;                    // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK;           // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST;                 // Set Software reset enable
  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK/Baudrate [if N > 16 continue with step 3, otherwise with step 2]
  // N = SMCLK / 4,800 => 8,000,000 / 4,800 = 1666.667
  // 2. OS16 = 0, UCBRx = INT(N) [continue with step 4]
  // 3. OS16 = 1, UCx = INT(N/16), UCFx = INT([(N/16) – INT(N/16)] × 16)
  // UCx = INT(N/16) = 1666.667/16 => 104
  // UCFx = INT([(N/16) – INT(N/16)] × 16) = ([1666.667/16-INT(1666.667/16)]*16) =>
  // (104.1666875-104)*16=>0.167*16=2
  // 4. UCSx can be found by looking up the fractional part of N ( = N - INT(N) ) in Table 18-4
  // Decicmal of SMCLK / 8,000,000 / 4,800 = 1666.667 => 0.667 yields 0xD6
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx  neg   pos  neg  pos
  // 8000000 4800     1     104    2  0xD6 -0.08 0.04 -0.10 0.14
  UCA1BRW = BAUD;                       // 4,800 baud
 
 
 // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
  UCA1MCTLW = IDK;
  UCA1CTL1 &= ~UCSWRST;                 // Release from reset
  UCA1IE |= UCRXIE;                     // Enable RX interrupt
}

//--------------------------------------------------------------------------- 
// Function name: USCI_A0_ISR
// 
// Description: This function handles serial interrupts.
// 
// Passed : no variables passed 
// Locals: temp
// Returned: no values returned 
// Globals: usb_rx_ring_wr, USB_Char_Rx
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA1IV,INTRANGE)){
  case RESET: break;                    // Vector 0 - no interrupt
  case RXIFG:                           // Vector 2 - RXIFG
    temp = gps_rx_ring_wr++;
    GPS_Char_Rx[temp] = UCA1RXBUF;      // RX -> USB_Char_Rx character
    if(GPS_Char_Rx[temp] == LF){
      for(i = RESET; i < LARGE_RING_SIZE; i++){
        NEMA_BUF[i] = GPS_Char_Rx[i];
        GPS_Char_Rx[i] = RESET;
      }
      gps_rx_ring_wr = BEGINNING;
      parsenow = TRUE;
    }
    if(gps_rx_ring_wr >= LARGE_RING_SIZE){
      gps_rx_ring_wr = BEGINNING;       // Circular buffer back to beginning
    }
    break;
  case TXIFG: break;                    // Vector 4 - TXIFG
  default: break;
 }
}

 
//--------------------------------------------------------------------------- 
// Function name: Project6
// 
// Description: This function passes the transfer pointer to the buffer.
// 
// Passed : no variables passed 
// Locals: no variables declared
// Returned: no values returned 
// Globals: temptx, start
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void Project6(void){
  if(start == PRESSED){
    while(ALWAYS){
      UCA1TXBUF = *(USB_Char_Tx + temptx);
      temptx++;
      five_msec_delay(INCREMENT);
      if(temptx > MAXPLACES){
        start = RESET;
        temptx = RESET;
        break;
      }
    }
  }
}
    

//--------------------------------------------------------------------------- 
// Function name: increment_Rx
// 
// Description: This function increments the received value.
// 
// Passed : no variables passed 
// Locals: places, placeinit, exponent, Rx_num
// Returned: no values returned 
// Globals: firsttime, increment, start, USB_Char_Rx, USB_Char_Tx
//
// Jason Zicherman
// February 2015
// Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//---------------------------------------------------------------------------
void increment_Rx(void){
  if(increment == PRESSED){
    if(firsttime == INCREMENT){
      UCA1TXBUF = RESET;
      for(i = RESET; i < MAXPLACES; i++) *(USB_Char_Rx + i) = SPACECHAR;
      *USB_Char_Rx = ZEROASCII + INCREMENT;
      for(i = RESET; i < MAXPLACES; i++) *(USB_Char_Tx + i) = SPACECHAR;
      firsttime = RESET;
    }
    lcd_out("               ",LCD_LINE_1);
    lcd_out(USB_Char_Rx,LCD_LINE_1);
    lcd_out("               ",LCD_LINE_2);
    int places = RESET;
    int placeinit = RESET;
    int exponent = PRESSED;
    int Rx_num = RESET;
    while(*(USB_Char_Rx + places) >= ZEROASCII && *(USB_Char_Rx + places) <= NINEASCII){
      places++;
    }
    placeinit = places;
    places--;
    while(places >= RESET){
      Rx_num += (*(USB_Char_Rx + places) - ZEROASCII)*exponent;
      exponent *= MASK;
      places--;
    }
    
 
places = placeinit;
    Rx_num++;
    if((Rx_num == RESET) || (Rx_num == MASK) || (Rx_num == SHIFTTWO) || (Rx_num == SHIFTTHREE) || (Rx_num == SHIFTFOUR)){
      places++;
      placeinit++;
    }
    else exponent /= MASK;
    while(places > RESET){
      *(USB_Char_Tx + (placeinit-places)) = (((Rx_num/exponent)%MASK)|ASCIICONV);
      places--;
      exponent /= MASK;
    }
    increment = RESET;
    five_msec_delay(SHIFTTWO);
    start = PRESSED;
    UCA1IE |= UCRXIE;
  }
