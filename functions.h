//------------------------------------------------------------------------------
//  Description: This file contains a list of all functions used in this project
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);


// Function prototypes clocks
void Init_Clocks(void);


// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_B2(void);
void TimerB0code(void);
void usleep10(unsigned int usec);
void five_more_msec_mom(unsigned int fivemsec);
void five_msec_sleep(unsigned int fivemsec);
void Init_Timer_A0(void);
void Init_Timer_A1(void);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
//void Init_PortJ(char gps_state);
void Init_PortJ(char clock_state);

// LCD Prototypes
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);
void lcd_out(char *s, char line);
void lcd_write(char data, char command);
void lcd_command( char data);

// Wheels
void wheels_off(void);
void right_wheel_fwd(void);
void right_wheel_rev(void);
void right_wheel_off(void);
void left_wheel_fwd(void);
void left_wheel_rev(void);
void left_wheel_off(void);
void drive_forward(void);
void drive_reverse(void);

