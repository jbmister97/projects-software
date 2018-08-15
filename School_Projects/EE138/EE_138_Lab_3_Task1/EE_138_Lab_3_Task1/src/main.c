////////////////////////////////////////////////////////////////////////////////////// 
////	Lab 3 - PWM
////		-SAMPLE CODE DOES NOT WORK-
////			- set up appropriate registers
////			- set up TC pointer 
//////////////////////////////////////////////////////////////////////////////////////

#include <asf.h>
#include <math.h>
void Simple_Clk_Init(void);
void enable_port(void);
void enable_tc_clocks(void);
void enable_tc(void);

//setup a the correct TC pointer for the corresponding pins. (use table 5-1 as a reference)
//there are multiple TC #'s, choose the one that ties to the specified port utilized

volatile int sinarr[15] = {0}; // array to store 15 sine wave values for the duty cycles
volatile int wait; // variable for delay purposes
Tc *tc2 = TC2; // pointer to TC2

int main (void)
{
	Simple_Clk_Init();
	/* Enable the timer*/
	enable_tc();
	int i;
	double x;
	//We used the math header file to get access to the sin() function
	for(i = 0; i < 15; i++){ // generate the sine wave values for the duty cycles and store it in the array "sinarr" with 15 sample points
		x = (2 * 3.14 * i / 15);
		sinarr[i] = ((sin(x) + 1)*0.5)*16;
		}
	

	while(1)
	{
		while(tc2 ->COUNT8.STATUS.bit.STOP & TC_STATUS_SYNCBUSY){}; // wait for TC
			tc2 -> COUNT8.CC[1].reg = sinarr[i]; // send each element of the array one by one to the CC[1] register
			i++;
			if(i > 14){i = 0;} // reset the array value to first
		while(wait < 100){wait++;} // additional wait time to help stabilize the waveform
		wait = 0;
	}
}

/* Set correct PA pins as TC pins for PWM operation */
void enable_port(void)
{
	//setup pins
	Port *ports = PORT_INSTS;
	PortGroup *por = &(ports->Group[0]);
	
	por->PINCFG[13].bit.PMUXEN = 0x1;		// set to correct pin configuration
	por->PMUX[6].bit.PMUXO = 0x4;			// set to correct peripheral

}

/* Perform Clock configuration to source the TC 
1) ENABLE THE APBC CLOCK FOR THE CORREECT MODULE
2) WRITE THE PROPER GENERIC CLOCK SELETION ID*/
void enable_tc_clocks(void)
{
	PM->APBCMASK.reg |= 1u << 10;  	// PM_APBCMASK TC2 is in the bit 10 position (page 92)
	
	uint32_t temp= 0x14;   		// ID for tc2,tc3 is 0x14  (see table 14-2)
	temp |= 0<<8;         			//  Selection Generic clock generator 0
	GCLK->CLKCTRL.reg=temp;   		//  Setup in the CLKCTRL register
	GCLK->CLKCTRL.reg |= 0x1u << 14;    	// enable it.
}

/* Configure the basic timer/counter to have a period of________ or a frequency of _________  */
void enable_tc(void)
{
	enable_port();
	enable_tc_clocks();
	
	// table of registers on page 447
	/* Set up CTRLA */
	/* 
	
	
		ex: pt->COUNT8.registername.reg = x;
	
	Set the 
	1) counter mode
	2) prescaler
	3) set the PRESCSYNC bits to PRESC from table 27-4 in the datasheet
	*/

	tc2 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc2 -> COUNT8.CTRLA.bit.PRESCALER = 0x1; // divide the clock by 2
	tc2 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc2 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM
	/* Write a suitable value to fix duty cycle and period.*/
	tc2 -> COUNT8.PER.reg = 16; // set the counter to count up to 16
	tc2 -> COUNT8.CC[1].reg = 8; // set the duty cycle to 50% (for test purposes)


	/*Enable TC*/
	tc2 -> COUNT8.CTRLA.reg |= 0x2;
}

//Simple Clock Initialization
void Simple_Clk_Init(void)
{
	/* Various bits in the INTFLAG register can be set to one at startup.
	   This will ensure that these bits are cleared */
	
	SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET |
			SYSCTRL_INTFLAG_DFLLRDY;
			
	system_flash_set_waitstates(0);  		//Clock_flash wait state =0

	SYSCTRL_OSC8M_Type temp = SYSCTRL->OSC8M;      	/* for OSC8M initialization  */

	temp.bit.PRESC    = 0;    			// no divide, i.e., set clock=8Mhz  (see page 170)
	temp.bit.ONDEMAND = 1;    			//  On-demand is true
	temp.bit.RUNSTDBY = 0;    			//  Standby is false
	
	SYSCTRL->OSC8M = temp;

	SYSCTRL->OSC8M.reg |= 0x1u << 1;  		// SYSCTRL_OSC8M_ENABLE bit = bit-1 (page 170)
	
	PM->CPUSEL.reg = (uint32_t)0;    		// CPU and BUS clocks Divide by 1  (see page 110)
	PM->APBASEL.reg = (uint32_t)0;     		// APBA clock 0= Divide by 1  (see page 110)
	PM->APBBSEL.reg = (uint32_t)0;     		// APBB clock 0= Divide by 1  (see page 110)
	PM->APBCSEL.reg = (uint32_t)0;     		// APBB clock 0= Divide by 1  (see page 110)

	PM->APBAMASK.reg |= 01u<<3;   			// Enable Generic clock controller clock (page 127)

	/* Software reset Generic clock to ensure it is re-initialized correctly */

	GCLK->CTRL.reg = 0x1u << 0;   			// Reset gen. clock (see page 94)
	while (GCLK->CTRL.reg & 0x1u ) {  /* Wait for reset to complete */ }
	
	// Initialization and enable generic clock #0

	*((uint8_t*)&GCLK->GENDIV.reg) = 0;  		// Select GCLK0 (page 104, Table 14-10)

	GCLK->GENDIV.reg  = 0x0100;   		 	// Divide by 1 for GCLK #0 (page 104)

	GCLK->GENCTRL.reg = 0x030600;  		 	// GCLK#0 enable, Source=6(OSC8M), IDC=1 (page 101)
}
