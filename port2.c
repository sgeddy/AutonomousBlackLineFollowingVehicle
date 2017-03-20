//------------------------------------------------------------------------------
//  Description: This file contains the routine for Port 2
//
//  Tyler Cheek
//  February 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//===========================================================================
// Init_Port2
// Purpose: Initialize Port 2
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2 CCIOA capture: CCI0A input
// 0 1 1 - TB2 CCIOA compare: Out0
// 1 0 0 - Transmit Data - eUSCI_A0 UART mode
// 1 0 1 - Slave in, master out - eUSCI_A0 SPI mode
// 1 1 X - TB0 clock input
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2 CCR1 capture: CCI1A
// 0 1 1 - TA0 CCR2 compare: Out1
// 1 0 0 - Receive data ? eUSCI_A0 UART mode
// 1 0 1 - Slave out, master in ? eUSCI_A0 SPI mode
// 1 1 X - Analog input A1 - ADC, Comparator_D input CD1, Input for an external reference voltage to the ADC
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2 CCR2 capture: CCI2A input
// 0 1 1 - Tb2 CCR2 compare: Out2
// 1 0 0 - Clock signal input ? eUSCI_B0 SPI slave mod
// 1 0 1 - Clock signal output ? eUSCI_B0 SPI master mode
// 1 1 X - Analog input A2 - ADC, Comparator_D input CD2
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR0 capture: CCI0B
// 0 1 1 - TA0 CCR0 compare: Out0
// 1 0 X - Slave transmit enable ? eUSCI_A1 SPI mode
// 1 1 X - Analog input A6 - ADC, Comparator_D input CD10
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR0 capture: CCI0B input
// 0 1 1 - TA1 CCR1 compare: Out0
// 1 0 X - Clock signal input ? eUSCI_A1 SPI slave mode, Clock signal output ? eUSCI_A1 SPI master mode (not available on deviceswithout eUSCI_A1)
// 1 1 X - Analog input A4 - ADC, Comparator_D input CD4
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR0 capture: CCI0B input
// 0 1 1 - TBO CCR0 compare: Out0
// 1 0 X - Clock signal input - eUSCI_A0 SPI slave, Clock signal output - eUSCI_A0 SPI master
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR1 capture: CCI1B input
// 0 1 1 - TB1 CCR1 compare: Out1
// 1 0 X - Transmit data ? eUSCI_A1 UART mode
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Tyler Cheek
// Date: February 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
void Init_Port2(void){
// Set Selections bits
P2SEL0 = CLEAR_REGISTER; // P2 set default as I/0
P2SEL1 = CLEAR_REGISTER; // P2 set default as I/0
P2SEL0 &= ~USB_TXD; 
P2SEL1 |= USB_TXD; 
P2SEL0 &= ~USB_RXD; 
P2SEL1 |= USB_RXD; 
P2SEL0 &= ~SPI_SCK; 
P2SEL1 |= SPI_SCK; 
P2SEL0 &= ~CPU_TXD; 
P2SEL1 |= CPU_TXD; 
P2SEL0 &= ~CPU_RXD; 
P2SEL1 |= CPU_RXD; 

//Enable resistors
P2REN |= SPI_SCK; // Enable pullup resistor
}
