/**
 * EE138 Lab #4
 */

#include <asf.h>

void enable_adc_clocks(void);
void init_adc(void);
void Simple_Clk_Init(void);
void configure_dac(void);
void configure_dac_clock(void);
void enable_tc_clocks(void);
void enable_tc(void);
void enable_interrupt(void);

Adc *adc = ADC; // pointer for ADC
Dac *dac = DAC; // pointer for DAC
Tc *tc4 = TC4; // pointer to TC4

//variables for filter equation
volatile float y, y1, y2; 
volatile float u, u1, u2;

float adcvalue;

int main (void)
{	
	Simple_Clk_Init();
	enable_tc_clocks();
	enable_tc();
	enable_adc_clocks();
	init_adc();
	configure_dac_clock();
	configure_dac();
	enable_interrupt();
	
	y=y1=y2=u=u1=u2=0;

	while(1){}
}

//used table 5-1 (Page 11) to find which TC number to use
void TC4_Handler(void){
	//ADC portion
	adc -> SWTRIG.reg = 0x2;
	while(!(adc -> INTFLAG.bit.RESRDY));
	adcvalue = (adc -> RESULT.reg); // Grab ADC conversion
	u = adcvalue/4.0; // convert adc result into a 10-bit number (right shift 2 = divide by 4)
	// (ADC portion takes 30 microseconds for adc portion)

	///////////////////////////////////////////////////////////////
	// Filter equation portion
	y = u - 1.48*u1 + 0.9891*u2 + 1.373*y1 - 0.8819*y2;
	y2 = y1;
	y1 = y;
	u2 = u1;
	u1 = u;
	//(filter portion takes 287.5 microseconds)

	///////////////////////////////////////////////////////////////
	// DAC portion
	while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {}
	dac -> DATABUF.reg = y; //send filtered value into DAC
	//DAC portion takes 17.5 microseconds

	///////////////////////////////////////////////////////////////
	tc4 ->COUNT8.INTFLAG.bit.OVF = 0x1;
}

void enable_interrupt(void)
{
	NVIC -> ISER[0] |= (1u << 17);
}

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
	enable_tc_clocks();	
	// table of registers on page 447

	tc4 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc4 -> COUNT8.CTRLA.bit.PRESCALER = 0x5; // divide the clock by 64
	tc4 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc4 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM

	tc4 -> COUNT8.PER.reg = 250; // set the period to 250 to get 500Hz sampling rate

	tc4 ->COUNT8.INTENSET.bit.OVF = 0x1;
	/*Enable TC*/
	tc4 -> COUNT8.CTRLA.reg |= 0x2;
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
	Port *ports = PORT_INSTS;
	PortGroup *por = &(ports->Group[0]);
	adc -> CTRLA.reg = 0x0;				//ADC block is disabled
	
	// you will need to configure 5 registers (check page 486 for table of them)
	adc -> REFCTRL.reg = 0x2; //(Page 490) Vddana is 3.3V
	adc -> AVGCTRL.reg = 0x0;
	adc -> SAMPCTRL.reg = 0x1;		// ADC Clock is 8MHz

	adc -> CTRLB.bit.PRESCALER = 0x1; // divide by 2
	adc -> CTRLB.bit.RESSEL = 0x0; // 12-bit value in result

	adc -> INPUTCTRL.bit.MUXPOS = 0x13;
	adc -> INPUTCTRL.bit.MUXNEG = 0x18;
	adc -> INPUTCTRL.bit.GAIN = 0xF;
	
	// config PA11 to be owned by ADC Peripheral
	
	por -> PMUX[5].bit.PMUXO = 0x1;		//refer to pg304 data sheet
	por -> PINCFG[11].bit.PMUXEN = 0x1;	//refer to pg304 data sheet
	
	adc -> CTRLA.reg = 0x2;				//Enable ADC
}

void configure_dac_clock(void)
{
	PM->APBCMASK.reg |= (1u << 18); 			// PM_APBCMASK DAC is in the bit[18] position
	
	uint32_t temp = 0x1A; 			// ID for DAC is 0x1A (see table 14-2)
	temp |= 0<<8; 					// Selection Generic clock generator 0
	GCLK->CLKCTRL.reg = temp; 			// Setup in the CLKCTRL register
	GCLK->CLKCTRL.reg |= 0x1u << 14; 		// enable it.
}

void configure_dac(void)
{
	//set pin as output for the dac
	Port *ports = PORT_INSTS;
	PortGroup *por = &(ports->Group[0]);
	
	por->PINCFG[2].bit.PMUXEN = 0x1;		// set to correct pin configuration
	por->PMUX[1].bit.PMUXE = 0x1;			// set to correct peripheral

	dac ->CTRLA.reg = 0x0;
	while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {
		/* wait until the synchronization is complete */
	}

	/* Set reference voltage with CTRLB */ // Page 550
		dac -> CTRLB.bit.REFSEL = 0x1; // set reference voltage to AVcc, Vcc is 3.3V

	while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {
		/* Wait until the synchronization is complete */
	}

	/* Enable the module with CTRLA */
		dac -> CTRLA.reg |= 0x2; // set the enable bit (bit[1]) of the CTRLA register
	/* Enable selected output with CTRLB*/
		dac -> CTRLB.bit.EOEN = 0x1; // set the external output bit
}

//Simple Clock Initialization
void Simple_Clk_Init(void)
{
	/* Various bits in the INTFLAG register can be set to one at startup.
	   This will ensure that these bits are cleared */
	
	SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET |
			SYSCTRL_INTFLAG_DFLLRDY;
			
	system_flash_set_waitstates(0);  		//Clock_flash wait state = 0

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