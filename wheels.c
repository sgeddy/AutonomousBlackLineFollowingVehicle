//------------------------------------------------------------------------------
//  Description: System Configurations
//  Tells the compiler to provide the value in reg as an input to an 
//  inline assembly block.  Even though the block contains no instructions,
//  the compiler may not optimize it away, and is told that the value
//  may change and should not be relied upon.
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
volatile unsigned int DRIVING_FORWARD = FALSE;
volatile unsigned int DRIVING_BACKWARD = FALSE;
void wheels_off(void) {
    PJOUT &= ~(R_FORWARD);
    PJOUT &= ~(L_FORWARD);
    PJOUT &= ~(R_REVERSE);
    PJOUT &= ~(L_REVERSE);
}
void right_wheel_fwd(void) {
    PJOUT |= R_FORWARD;
}
void right_wheel_rev(void) {
    PJOUT |= R_REVERSE;
}
void right_wheel_off(void) {
    PJOUT &= ~(R_FORWARD);
    PJOUT &= ~(R_REVERSE);
}
void left_wheel_fwd(void) {
    PJOUT |= L_FORWARD;
}
void left_wheel_rev(void) {
 
    PJOUT |= L_REVERSE;
}
void left_wheel_off(void) {
    PJOUT &= ~(L_FORWARD);
    PJOUT &= ~(L_REVERSE);
}
void drive_forward(void) {
    DRIVING_FORWARD = TRUE;
    DRIVING_BACKWARD = FALSE;
    right_wheel_fwd();
    left_wheel_fwd();
}
void drive_reverse(void) {
    DRIVING_FORWARD = FALSE;
    DRIVING_BACKWARD = TRUE;
    right_wheel_rev();
    left_wheel_rev();  
}
