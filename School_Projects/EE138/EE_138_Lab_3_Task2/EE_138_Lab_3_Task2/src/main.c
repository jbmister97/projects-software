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
void enable_adc_clocks(void);
void init_adc(void);
float read_adc(void);

//setup a the correct TC pointer for the corresponding pins. (use table 5-1 as a reference)
//there are multiple TC #'s, choose the one that ties to the specified port utilized
Tc *tc4 = TC4; // pointer to TC4
Adc *adc = ADC; // pointer for the adc
PortGroup *porta = (PortGroup *)PORT; // pointer for group A pins

int main (void)
{
	Simple_Clk_Init();
	/* Enable the timer*/
	enable_tc();
	enable_adc_clocks();
	init_adc();
	int adcvalue; // variable for the adc result register value

	while(1)
	{	
		adcvalue = ((read_adc())/4096)*3300; // get the value from potentiometer that ranges from 0 to 3300
		if (300 < adcvalue < 3000) // create a limitation for the values so they do not get too close to zero or maximum
			tc4 -> COUNT8.CC[0].reg = 3300 - (adcvalue/20) - 25; // create the value for PA22
			tc4 ->COUNT8.CC[1].reg = adcvalue/20 + 550; // create the value for PA23

	}
}

/* Set correct PA pins as TC pins for PWM operation */
void enable_port(void)
{
	//setup pins
	Port *ports = PORT_INSTS;
	PortGroup *por = &(ports->Group[0]);
	
	por->PINCFG[23].bit.PMUXEN = 0x1;		// set to correct pin configuration
	por->PMUX[11].bit.PMUXO = 0x5;			// set to correct peripheral F
	por->PINCFG[22].bit.PMUXEN = 0x1;		// set to correct pin configuration
	por->PMUX[11].bit.PMUXE = 0x5;			// set to correct peripheral F

}

/* Perform Clock configuration to source the TC 
1) ENABLE THE APBC CLOCK FOR THE CORREECT MODULE
2) WRITE THE PROPER GENERIC CLOCK SELETION ID*/
void enable_tc_clocks(void)
{
	PM->APBCMASK.reg |= 1u << 12;  	// PM_APBCMASK TC4 is in the bit 12 position (page 111)
	
	uint32_t temp= 0x15;   		// ID for tc4 is 0x15  (see table 14-2, page 92)
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

	tc4 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc4 -> COUNT8.CTRLA.bit.PRESCALER = 0x1; // divide the clock by 2
	tc4 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc4 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM
	/* Write a suitable value to fix duty cycle and period.*/
	tc4 -> COUNT8.PER.reg = 3300; // set the counter to count up to 3300
	tc4 -> COUNT8.CC[1].reg = 1650; // set the duty cycle to 50% (for default)
	tc4 ->COUNT8.CC[0].reg = 1650;


	/*Enable TC*/
	tc4 -> COUNT8.CTRLA.reg |= 0x2;
}

float read_adc(void)
{
	// start the conversion
	adc -> SWTRIG.reg = 0x2;
	int ans;
	while(!(adc -> INTFLAG.bit.RESRDY));			//wait for conversion to be available
	ans = adc -> RESULT.reg;
	return(ans); 					//insert register where ADC store value
}

void enable_adc_clocks(void)
{
	PM->APBCMASK.reg |= 1u << 16; 			// PM_APBCMASK_______ is in the ___ position (Page 123)
	
	uint32_t temp = 0x17; 			// ID for ADC is 0x17 (see table 14-2) (Page 92)
	temp |= 0<<8; 					// Selection Generic clock generator 0
	GCLK->CLKCTRL.reg = temp; 			// Setup in the CLKCTRL register
	GCLK->CLKCTRL.reg |= 0x1u << 14; 		// enable it.
}

// initialize the on-board ADC system
void init_adc(void)
{
	adc -> CTRLA.reg = 0x0;				//ADC block is disabled
	
	// you will need to configure 5 registers (check page 486 for table of them)
	adc -> REFCTRL.reg = 0x2; //(Page 490) Vddana is 3.3V
	adc -> AVGCTRL.reg = 0x0;
	adc -> SAMPCTRL.reg = 0x0;		// ADC Clock is 8MHz

	adc -> CTRLB.bit.PRESCALER = 0x2; //
	adc -> CTRLB.bit.RESSEL = 0x0; // 12-bit value in result

	adc -> INPUTCTRL.bit.MUXPOS = 0x13;
	adc -> INPUTCTRL.bit.MUXNEG = 0x18;
	adc -> INPUTCTRL.bit.GAIN = 0xF;
	
	// config PA11 to be owned by ADC Peripheral
	
	porta -> PMUX[5].bit.PMUXO = 0x1;		//refer to pg304 data sheet
	porta -> PINCFG[11].bit.PMUXEN = 0x1;	//refer to pg304 data sheet
	porta -> DIRSET.reg = 1u << 13;
	porta -> OUTSET.reg = (1u << 13);
	
	adc -> CTRLA.reg = 0x2;				//Enable ADC
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
