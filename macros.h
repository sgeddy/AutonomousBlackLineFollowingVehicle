//------------------------------------------------------------------------------
//  Description: This file contains the macros used in all other files
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define TRUE                    (1)
#define INCREMENT               (1)
#define FALSE                   (0)
#define INIT                    (0)
#define CLEAR_REGISTER          (0x00)
#define FUNCTION_REGISTER       (0x01)
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1              (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2              (0xC0) // Position Cursor at Character 01 of Line 2
#define INPUT_SET               (0x00)
#define OUTPUT_SET              (0x01)
#define CIRCLE                  (1)
#define TRIANGLE                (2)
#define FIGURE_EIGHT            (3)
#define HALF_SECOND_MODULO      (8)
#define DECADE                  (10)

//Timer delays
#define TIME_DELAY                              (10)
#define TEN_CYCLES                              (5)
#define TWOHUNDREDFIFTY_MSEC_DELAY              (50)
#define DEBOUNCE_DELAY                          (5)
#define THREEHUNDREDSEVENTYFIVE_MSEC_DELAY      (75)
#define WTF_TOO_LARGE_DELAY                     (1000)
#define TS_DAMN_DIS_IS_HUGE                     (250)
#define TS_PRETTY_BIG                           (200)
#define TS_LARGE                                (150)
#define TS_MEDIUM                               (100)
#define TS_KIND_OF_SMALL                        (50)
#define TA0CCR0_INTERVAL                        (25000) // 8,000,000 / 8 / 2 / 25000 = 20Hz => 50msec
#define TA0CCR1_INTERVAL                        (2500)  // 8,000,000 / 8 / 2 / 2500 = 200Hz => 5msec
#define TA1CCR0_INTERVAL                        (1250)  // 10,000 / 1 / 8 / 1250 = 1Hz => 1sec
#define USECDELAY                               (14)
//LEDs
#define LED1                    (0x01) // LED 1
#define LED2                    (0x02) // LED 2
#define LED3                    (0x04) // LED 3
#define LED4                    (0x08) // LED 4
#define LED5                    (0x10) // LED 5
#define LED6                    (0x20) // LED 6
#define LED7                    (0x40) // LED 7
#define LED8                    (0x80) // LED 8

//Switches
#define SW1                     (0x01) // Switch 1
#define SW2                     (0x02) // Switch 2

//Port 1
#define V_DETECT_R              (0x01)
#define V_DETECT_L              (0x02)
#define IR_LED                  (0x04)
#define V_THUMB                 (0x08)
#define SPI_CS_LCD              (0x10) // LCD Chip Select
#define LCD_RESET               (0x20) // GPS Power Check from GPS
#define SPI_SIMO                (0x40) // SPI mode - slave in/master out of USCI_B0
#define RS_LCD                  (0x80) // RS_LCD Command / Data selection
#define SOMI_B                  (0x80) // SPI mode - slave out/master in of USCI_B0

//Port 2
#define USB_TXD                 (0x01) //
#define USB_RXD                 (0x02) //
#define SPI_SCK                 (0x04) //
#define CPU_TXD                 (0x08) // GPS Power Check from GPS
#define CPU_RXD                 (0x10) // SPI mode - slave in/master out of USCI_B0
#define GPS_PWRCHK              (0x10)
#define GPS_PWRCNTL             (0x20)
#define GPS_RESET               (0x40)
#define GPS_PWR                 (0x80)

//Port 3
#define LCD_BACKLITE            (0x08)

//Clocks
#define CSLOCK                  (0x01) // Any incorrect password locks registers
#define MCLK_FREQ               (8000000L)
#define SMCLK_FREQ              (8000000L)
#define SMCLK_DIV               (64)
#define USE_R_FORWARD           (0x00)
#define USE_SMCLK               (0x01)

//directions
#define R_FORWARD               (0x01)
#define L_FORWARD               (0x02)
#define R_REVERSE               (0x04)
#define L_REVERSE               (0x08)
