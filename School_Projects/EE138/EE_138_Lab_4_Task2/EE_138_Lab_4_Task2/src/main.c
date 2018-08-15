/**
 * EE138 Lab #4
 */

#include <asf.h>

void enable_adc_clocks(void);
void init_adc(void);
void Simple_Clk_Init(void);
void configure_dac(void);
void configure_dac_clock(void);
void enable_tc2_clocks(void);
void enable_tc4_clocks(void);
void enable_tc2(void);
void enable_tc4(void);
void enable_interrupt(void);
void display(int n);
void wait(int t);
void enable_eic_clock(void);
void configure_eic(void);
void enable_ports(void);
float read_adc(void);

Adc *adc = ADC; // pointer for ADC
Dac *dac = DAC; // pointer for DAC
Tc *tc2 = TC2; // pointer to TC2
Tc *tc4 = TC4; // pointer to TC4

//variables for filter equation
volatile float y, y1, y2; 
volatile float u, u1, u2;

float adcvalue, revolutions;
volatile float speed = 0;
volatile int filterspeed = 0;
int adcvaluepwm;
int number[4] = {0};
int count;
int startcalc;
volatile signed int eiccount = 0;
volatile signed int eiccounttemp = 0;
volatile int displayvalue = 0;

int main (void)
{	
	Simple_Clk_Init();
	enable_ports();
	enable_tc2(); // used tc2 for sampling counter
	enable_tc4(); // used tc4 for pwm
	enable_adc_clocks();
	init_adc();
	configure_dac_clock();
	configure_dac();
	enable_eic_clock();
	configure_eic();
	enable_interrupt();
	
	y=y1=u=u1=0;
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	PortGroup *porB = &(ports->Group[1]);
	porA->DIRSET.reg = (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7);
	porB->DIRSET.reg = (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6);

	while(1){
		//////////////////
		//PWM portion
		adcvaluepwm = ((read_adc())/4096)*255; // get the value from potentiometer that ranges from 0 to 255
		if ((adcvaluepwm >20) & (adcvaluepwm < 235)){ // create a limitation for the values so they do not get too close to zero or maximum
		tc4 -> COUNT8.CC[0].reg = 255 - (adcvaluepwm); // create the value for PA22
		tc4 ->COUNT8.CC[1].reg = adcvaluepwm; // create the value for PA23
		}
		/////////////////////////////////
		//Display portion
		displayvalue = filterspeed;
		porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
		porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06;
		porB -> OUTCLR.reg = PORT_PB07;
		number[3] = displayvalue/1000;
		display(number[3]);
		wait(5);
		porA -> OUTCLR.reg = PORT_PA06;
		porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
		porB -> OUTSET.reg = PORT_PB07;
		number[2] = (displayvalue - (number[3] * 1000)) / 100;
		display(number[2]);
		wait(5);
		porA -> OUTCLR.reg = PORT_PA05;
		porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
		porB -> OUTSET.reg = PORT_PB07;
		number[1] = (displayvalue - (number[3] * 1000) - (number[2] * 100)) / 10;
		display(number[1]);
		wait(5);
		porA -> OUTCLR.reg = PORT_PA04;
		porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
		porB -> OUTSET.reg = PORT_PB07;
		number[0] = (displayvalue - (number[3] * 1000) - (number[2] * 100) - (number[1] * 10));
		display(number[0]);
		wait(5);
	}
}


float read_adc(void)
{	// start the conversion
	adc -> SWTRIG.reg = 0x2;
	int ans;
	while(!(adc -> INTFLAG.bit.RESRDY));			//wait for conversion to be available
	ans = adc -> RESULT.reg;
	return(ans); 					//insert register where ADC store value
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

void enable_eic_clock(void){
	PM->APBAMASK.reg |= 1u << 6;  	// PM_APBAMASK EIC is in the bit 6 position (page 121)
	uint32_t temp= 0x03;   		// ID for eic is 0x03  (see table 14-2, page 91)
	temp |= 0<<8;         			//  Selection Generic clock generator 0
	GCLK->CLKCTRL.reg=temp;   		//  Setup in the CLKCTRL register
	GCLK->CLKCTRL.reg |= 0x1u << 14;    	// enable it.
}

// EIC register table page 245
void configure_eic(void){
	EIC ->CTRL.reg = 0x0; // disable eic
	EIC ->INTENSET.bit.EXTINT8 = 1; // enable interrupt 8 for PA28
	EIC ->CONFIG[1].bit.SENSE0 = 1; // set to trigger on rising edge
	//EIC ->EVCTRL.bit.EXTINTEO8 = 1;
	//EIC ->WAKEUP.bit.WAKEUPEN8 = 1;
	EIC ->CTRL.reg |= 0x2; // enable eic
}

void EIC_Handler(void){
	Port *ports = PORT_INSTS;
	PortGroup *porB = &(ports->Group[1]);

	if (porB->IN.reg & (1u << 14)){eiccount--;} // if phase B is high while A is high count down
	else{eiccount++;} // if phase B is low while A is high count up

	EIC ->INTFLAG.bit.EXTINT8 = 1; // clear eic interrupt flag
}

//used table 5-1 (Page 11) to find which TC number to use
void TC2_Handler(void){
	//Speed calculation portion
	if (eiccount < 0){eiccounttemp = eiccount*-1;} // make count positive
	else {eiccounttemp = eiccount;}
	revolutions = eiccounttemp*30.0; // (eiccount/(400 per rev))*(200 samples/sec)*(60secs)
	speed = revolutions;
	eiccount = 0; // reset count
	eiccounttemp = 0; // reset temporary count
	//Speed portion takes 35 microseconds
	
	///////////////////////////////////////////////////////////////
	// Filter equation portion
	u = speed;
	y = 0.9691*y1 + 0.03093*u1; // first order low pas filter function
	y1 = y;
	u1 = u;
	// Filter portion takes 77.5 microseconds
	filterspeed = y; // update rpm

	///////////////////////////////////////////////////////////////
	// DAC portion
	while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {}
	dac -> DATABUF.reg = y; //send filtered value into DAC
	
	///////////////////////////////////////////////////////////////
	tc2 ->COUNT8.INTFLAG.bit.OVF = 0x1;
}

void enable_interrupt(void)
{
	NVIC -> ISER[0] |= (1u << 15) | (1u << 4); // (table is on page 26)
	// tc2 interrupt is bit 15 and eic is bit 4
}

void enable_ports(void){
	Port *ports = PORT_INSTS;
	PortGroup *pora = &(ports->Group[0]);
	PortGroup *porb = &(ports->Group[1]);
	
	//For PWM input
	pora->PINCFG[23].bit.PMUXEN = 0x1;		// set to correct pin configuration
	pora->PMUX[11].bit.PMUXO = 0x5;			// set to correct peripheral F
	pora->PINCFG[22].bit.PMUXEN = 0x1;		// set to correct pin configuration
	pora->PMUX[11].bit.PMUXE = 0x5;			// set to correct peripheral F
	////////////////////////////////////////
	// For EIC logic
	pora->PINCFG[28].bit.PMUXEN = 0x1;		// set to correct pin configuration
	pora->PMUX[14].bit.PMUXE = 0x0;			// set to correct peripheral A for EIC
	porb->PINCFG[14].bit.PMUXEN = 0x1;		// set to correct pin configuration
	porb->PMUX[7].bit.PMUXE = 0x0;			// set to correct peripheral A for EIC
}

void enable_tc2_clocks(void){
	//For TC2 (filter counter)
	PM->APBCMASK.reg |= 1u << 10;  	// PM_APBCMASK TC2 is in the bit 10 position (page 111)
	
	uint32_t temp= 0x14;   		// ID for tc2 is 0x14  (see table 14-2, page 92)
	temp |= 0<<8;         			//  Selection Generic clock generator 0
	GCLK->CLKCTRL.reg=temp;   		//  Setup in the CLKCTRL register
	GCLK->CLKCTRL.reg |= 0x1u << 14;    	// enable it.
}

void enable_tc4_clocks(void){
	// For TC4 (PWM)
	PM->APBCMASK.reg |= 1u << 12;  	// PM_APBCMASK TC4 is in the bit 12 position (page 111)
	
	uint32_t temp= 0x15;   		// ID for tc4 is 0x15  (see table 14-2, page 92)
	temp |= 0<<8;         			//  Selection Generic clock generator 0
	GCLK->CLKCTRL.reg=temp;   		//  Setup in the CLKCTRL register
	GCLK->CLKCTRL.reg |= 0x1u << 14;    	// enable it.
}

/* Configure the basic timer/counter to have a period of________ or a frequency of _________  */
void enable_tc2(void)
{
	enable_tc2_clocks();	
	// table of registers on page 447
	
	tc2 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc2 -> COUNT8.CTRLA.bit.PRESCALER = 0x6; // divide the clock by 256
	tc2 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc2 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM

	tc2 -> COUNT8.PER.reg = 156; // set the period to 156 to get 200Hz sampling rate

	tc2 ->COUNT8.INTENSET.bit.OVF = 0x1;
	/*Enable TC*/
	tc2 -> COUNT8.CTRLA.reg |= 0x2;
}

void enable_tc4(void){
	enable_tc4_clocks();
	tc4 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc4 -> COUNT8.CTRLA.bit.PRESCALER = 0x1; // divide the clock by 2
	tc4 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc4 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM
	/* Write a suitable value to fix duty cycle and period.*/
	tc4 -> COUNT8.PER.reg = 255; // set the counter to count up to 255

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
	PortGroup *pora = &(ports->Group[0]);
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
	
	pora -> PMUX[5].bit.PMUXO = 0x1;		//refer to pg304 data sheet
	pora -> PINCFG[11].bit.PMUXEN = 0x1;	//refer to pg304 data sheet
	pora -> DIRSET.reg = 1u << 13;
	pora -> OUTSET.reg = (1u << 13);
	
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