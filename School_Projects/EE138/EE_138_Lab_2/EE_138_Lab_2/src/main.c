////////////////////////////////////////////////////////////////////////////////////// 
////	Lab 2 - Analog To Digital Converter 
////		-SAMPLE CODE DOES NOT WORK-
////			- insert variables into appropriate registers
////			- set up ADC pointer (similar to port_inst setup)
//////////////////////////////////////////////////////////////////////////////////////

#include <asf.h>

void enable_adc_clocks(void);
void init_adc(void);
void display(int n);
float read_adc(void);
void Simple_Clk_Init(void);
void wait(int t);
PortGroup *porta = (PortGroup *)PORT;
/*	initialize ADC pointer here  	*/		// define a pointer to the ADC block
Adc *adc = ADC;

int count;
float ans;

float read_adc(void)
{
	// start the conversion
		adc -> SWTRIG.reg = 0x2;
		
	while(!(adc -> INTFLAG.bit.RESRDY));			//wait for conversion to be available
		ans = adc -> RESULT.reg;
	return(ans); 					//insert register where ADC store value
	
}

int main (void)
{	
	Simple_Clk_Init();
	enable_adc_clocks();
	init_adc();

	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	PortGroup *porB = &(ports->Group[1]);
	porA->DIRSET.reg = (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7) | (1u << 13);
	porB->DIRSET.reg = (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7);
	porA -> OUTSET.reg = (1u << 13);
		
	float x;
	int number[4] = {0, 0, 0, 0};
	
	while(1)
	{
			x = (float) (read_adc());			//store variable from ADC into variable "x"
			x = (x/4094) * 3300;
			porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
			porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06;
			porB -> OUTCLR.reg = PORT_PB07;
			number[3] = x/1000;
			display(number[3]);
			wait(5);
			porA -> OUTCLR.reg = PORT_PA06;
			porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
			porB -> OUTSET.reg = PORT_PB07;
			number[2] = (x - (number[3] * 1000)) / 100;
			display(number[2]);
			wait(5);
			porA -> OUTCLR.reg = PORT_PA05;
			porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
			porB -> OUTSET.reg = PORT_PB07;
			number[1] = (x - (number[3] * 1000) - (number[2] * 100)) / 10;
			display(number[1]);
			wait(5);
			porA -> OUTCLR.reg = PORT_PA04;
			porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
			porB -> OUTSET.reg = PORT_PB07;
			number[0] = (x - (number[3] * 1000) - (number[2] * 100) - (number[1] * 10));
			display(number[0]);
			wait(5);
	}
}

void display(int n){
	Port *ports = PORT_INSTS;
	PortGroup *porB = &(ports->Group[1]);
	porB -> DIRSET.reg = PORT_PB06 | PORT_PB05 | PORT_PB04 | PORT_PB03 | PORT_PB02 | PORT_PB01 | PORT_PB00;
		if (n == 0){ // port outputs to display 0 on the 7-segment display
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB03 | PORT_PB04 | PORT_PB05;
			porB -> OUTSET.reg = PORT_PB06;
		}
		if (n == 1){
			porB -> OUTCLR.reg = PORT_PB01 | PORT_PB02 ;
			porB -> OUTSET.reg = PORT_PB00 | PORT_PB03| PORT_PB04 | PORT_PB05 | PORT_PB06;
		}
		if (n == 2){
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB03 | PORT_PB04 | PORT_PB06;
			porB -> OUTSET.reg = PORT_PB02 | PORT_PB05;
		}
		if (n == 3){
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB03 | PORT_PB06;
			porB -> OUTSET.reg = PORT_PB04 | PORT_PB05;
		}
		if (n == 4){
			porB -> OUTCLR.reg = PORT_PB01 | PORT_PB02 | PORT_PB05 | PORT_PB06;
			porB -> OUTSET.reg = PORT_PB00 | PORT_PB03 | PORT_PB04;
		}
		if (n == 5){
			porB -> OUTSET.reg = PORT_PB01 | PORT_PB04 | PORT_PB07;
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB02 | PORT_PB03 | PORT_PB05 | PORT_PB06;
		}
		if (n == 6){
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB02 | PORT_PB03 | PORT_PB04 | PORT_PB05 | PORT_PB06;
			porB -> OUTSET.reg = PORT_PB01;
		}
		if (n == 7){
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02;
			porB -> OUTSET.reg = PORT_PB03 | PORT_PB04 | PORT_PB05 | PORT_PB06;
		}
		if (n == 8){
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB03 | PORT_PB04 | PORT_PB05 | PORT_PB06;
		}
		if (n == 9){
			porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB05 | PORT_PB06;
			porB -> OUTSET.reg = PORT_PB03 | PORT_PB04;
		}
		return;
}

// set up generic clock for ADC
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
	
	adc -> CTRLA.reg = 0x2;				//Enable ADC	
}

//time delay function
void wait(int t)
{
	count = 0;
	while (count < t*1000)
	{
		count++;
	}
}
	
//Simple Clock Initialization
void Simple_Clk_Init(void)
{
	/* Various bits in the INTFLAG register can be set to one at startup.
	   This will ensure that these bits are cleared */
	
	SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET |
			SYSCTRL_INTFLAG_DFLLRDY;
			
	system_flash_set_waitstates(0);  	//Clock_flash wait state =0

	SYSCTRL_OSC8M_Type temp = SYSCTRL->OSC8M;      /* for OSC8M initialization  */

	temp.bit.PRESC    = 0;    		// no divide, i.e., set clock=8Mhz  (see page 170)
	temp.bit.ONDEMAND = 1;    		// On-demand is true
	temp.bit.RUNSTDBY = 0;    		// Standby is false
	
	SYSCTRL->OSC8M = temp;

	SYSCTRL->OSC8M.reg |= 0x1u << 1;  	// SYSCTRL_OSC8M_ENABLE bit = bit-1 (page 170)
	
	PM->CPUSEL.reg = (uint32_t)0;    	// CPU and BUS clocks Divide by 1  (see page 110)
	PM->APBASEL.reg = (uint32_t)0;     	// APBA clock 0= Divide by 1  (see page 110)
	PM->APBBSEL.reg = (uint32_t)0;     	// APBB clock 0= Divide by 1  (see page 110)
	PM->APBCSEL.reg = (uint32_t)0;     	// APBB clock 0= Divide by 1  (see page 110)

	PM->APBAMASK.reg |= 01u<<3;   		// Enable Generic clock controller clock (page 127)

	/* Software reset Generic clock to ensure it is re-initialized correctly */

	GCLK->CTRL.reg = 0x1u << 0;   		// Reset gen. clock (see page 94)
	while (GCLK->CTRL.reg & 0x1u ) {  /* Wait for reset to complete */ }
	
	// Initialization and enable generic clock #0

	*((uint8_t*)&GCLK->GENDIV.reg) = 0;  	// Select GCLK0 (page 104, Table 14-10)

	GCLK->GENDIV.reg  = 0x0100;   		// Divide by 1 for GCLK #0 (page 104)

	GCLK->GENCTRL.reg = 0x030600;  		// GCLK#0 enable, Source=6(OSC8M), IDC=1 (page 101)
}