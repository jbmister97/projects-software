/*
LAB4B: Working with MSP430 Analog to Digital Converter
*/

#include <msp430g2553.h>

#ifndef TIMER0_A1_VECTOR
#define TIMER0_A1_VECTOR    TIMERA1_VECTOR
#define TIMER0_A0_VECTOR    TIMERA0_VECTOR
#endif

volatile long tempRaw;
int temp[64];
int i;
int minimum = 1023, maximum = 0;

void FaultRoutine(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer
  P1DIR = 0x41;                       // P1.0&6 outputs
  P1OUT = 0;                          // LEDs off

// if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)
//   FaultRoutine();		        // If cal data is erased
 				               // run FaultRoutine()
// BCSCTL1 = CALBC1_1MHZ; 		  // Set range
  DCOCTL = CALDCO_1MHZ;  		  // Set DCO step + modulation

  BCSCTL3 |= LFXT1S_2;                 // LFXT1 = VLO
  IFG1 &= ~OFIFG;                      // Clear OSCFault flag
  BCSCTL2 |= SELM_0 + DIVM_3 + DIVS_3; // MCLK = DCO/8

  for(i = 0; i < 63; i++)
  {
	ADC10CTL1 = INCH_10 + ADC10DIV_0;   // Temp Sensor ADC10CLK
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;
	_delay_cycles(5);                  // Wait for ADC Ref to settle
	ADC10CTL0 |= ENC + ADC10SC;         // Sampling & conversion start

   P1OUT = 0x40; 			   // green LED on
   _delay_cycles(100);

   ADC10CTL0 &= ~ENC;
   ADC10CTL0 &= ~(REFON + ADC10ON);
   tempRaw = ADC10MEM;
   temp[i] = tempRaw;

   P1OUT = 0; 		                // green LED off
  if (temp[i] < minimum)
  {minimum = temp[i];}
  if (temp[i] > maximum)
  {maximum = temp[i];}
   _delay_cycles(12500);
  }
}

void FaultRoutine(void)
 {
   P1OUT = 0x01;                       // red LED on
   while(1); 			         // TRAP
 }
