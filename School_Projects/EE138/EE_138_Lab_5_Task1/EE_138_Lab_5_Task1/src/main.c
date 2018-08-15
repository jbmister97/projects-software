/**
 * EE138 Lab #5
 */

#include <asf.h>

void Simple_Clk_Init(void);
void enable_tc2_clocks(void);
void enable_tc4_clocks(void);
void enable_tc2(void);
void enable_tc3(void);
void enable_tc4(void);
void enable_interrupt(void);
void display(int n);
void wait(int t);
void enable_eic_clock(void);
void configure_eic(void);
void enable_ports(void);
void state_machine(void);
void seg_display(void);
void speed_control(void);
void slow_down(void);
void speed_up(void);
Tc *tc2 = TC2; // pointer to TC2
Tc *tc3 = TC3; // pointer to TC3
Tc *tc4 = TC4; // pointer to TC4

//variables for filter equation
volatile float y, y1, y2; 
volatile float u, u1, u2;

float revolutions;
volatile float speed = 0;
volatile int filterspeed = 0;
int number[4] = {0};

volatile int state1 = 1;
int startcalc;
volatile signed int eiccount = 0;
volatile signed int eiccounttemp = 0;
volatile int displayvalue = 0;

volatile float Kp = 0.009; 
volatile float Ki = 0.54; //Kp*frequency
volatile float error = 0;
volatile float integral = 0;


//global variables
volatile float value = 0;
volatile int dcount = 0; // counter for the debouncing circuit
volatile int count = 0;
volatile int state = 0;
volatile int desiredspeed = 1501;
volatile int i;
volatile int inc;
volatile int input[4] = {0}; // array where user input is stored
volatile int input1[1] = {3};	
int a, b; // variables used
void verify_press(void); // checks how long a button is pressed
void verify_release(void); // checks how long a button is released
void get_input(void);
void display_idle(void);
void key_press (void);
int main (void)
{	
	Simple_Clk_Init();
	enable_ports();
	enable_tc2(); // used tc2 for sampling counter
	enable_tc4(); // used tc4 for pwm
	enable_tc3(); // used tc3 rpm calculations
	enable_eic_clock();
	configure_eic();
	enable_interrupt();
	
	y=y1=u=u1=0;

	while(1) {}
}

void state_machine(void){
	
	switch (state1) {
		
		case 1:	//Idle State
				tc4 ->COUNT8.CC[0].reg = 0; // set outputs to 0
				tc4 ->COUNT8.CC[1].reg = 0;
				break;

		case 2: //Accelerate (when 1 is pressed)
				speed_up(); //PI function for speeding up
	
				value = (int)((value / 4800) * 255); // scale the output of PI function to CC values
				tc4 ->COUNT8.CC[1].reg = value;
				tc4 ->COUNT8.CC[0].reg = 0 ;
				if (u > 1495){ // move onto stabilize state when speed is 1495-1505
					if (u < 1505){state1 = 3;}
				}
				break;

		case 3:	//Stabilize
				speed_control(); // PI function for stabilizing at 1500 rpm

				value = (int)((value / 4800) * 255);
				tc4 ->COUNT8.CC[1].reg = value;
				tc4 ->COUNT8.CC[0].reg = 0 ;
				break;	

		case 4: //Decelerate (when zero is pressed)
				slow_down(); // PI function for slowing down motor

				value = (int)((value / 4800) * 255);
				tc4 ->COUNT8.CC[1].reg = value;
				tc4 ->COUNT8.CC[0].reg = 0 ;
				
				if (u == 0){state1 = 1;} // when speed reaches 0 return to idle state
				break;
	}
}

void speed_up(void){
	error = (inc - u); // increment variable increases over time to speed up motor
	integral += (1/60.0)*error;
	value = (Kp*error) + (Ki*integral);
	inc += 4; // increment the inc variable by 4
}

void speed_control(void){
	error = (desiredspeed - u); // find error around desired speed (1500)
	integral += (1/60.0)*error;
	value = (Kp*error) + (Ki*integral);
	inc = u; // set current speed to inc variable (prepare for slow down state)
}

void slow_down(void){
	error = (inc - u); // find error for current speed
	integral += (1/60.0)*error;
	value = (Kp*error) + (Ki*integral);
	inc -= 4;  // decrease inc to slow down motor
}

void seg_display(void){
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	PortGroup *porB = &(ports->Group[1]);

	displayvalue = filterspeed;
	porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
	porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06;
	porB -> OUTCLR.reg = PORT_PB07;
	number[3] = displayvalue/1000;
	display(number[3]);
	wait(1);
	porA -> OUTCLR.reg = PORT_PA06;
	porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
	porB -> OUTSET.reg = PORT_PB07;
	number[2] = (displayvalue - (number[3] * 1000)) / 100;
	display(number[2]);
	wait(1);
	porA -> OUTCLR.reg = PORT_PA05;
	porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
	porB -> OUTSET.reg = PORT_PB07;
	number[1] = (displayvalue - (number[3] * 1000) - (number[2] * 100)) / 10;
	display(number[1]);
	wait(1);
	porA -> OUTCLR.reg = PORT_PA04;
	porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
	porB -> OUTSET.reg = PORT_PB07;
	number[0] = (displayvalue - (number[3] * 1000) - (number[2] * 100) - (number[1] * 10));
	display(number[0]);
	wait(1);
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
	u = speed;

	///////////////////////////////////////////////////////////////
	// Filter equation portion
	y = 0.9691*y1 + 0.03093*u1; // first order low pas filter function
	y1 = y;
	u1 = u;

	filterspeed = y; // update rpm

	///////////////////////////////////////////////////////////////
	tc2 ->COUNT8.INTFLAG.bit.OVF = 0x1;
}

void TC3_Handler(void){ // where all the input and state machine are called at 60Hz
	Port *ports = PORT_INSTS;
	//sets the group offset for the structure PortGroup in this case it is for group[0] or groupA
	// GroupA offset of 0x00				// GroupB offset of 0x80
	PortGroup *porA = &(ports->Group[0]);
	
	// Set the direction outputs for the 7-segment displays
	porA->DIRSET.reg = (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7);

	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

	switch(state){
		case 0:	// idle state
				// the displays are constantly refreshed so the numbers display while nothing is pressed
				porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06; // disable bottom three rows
				key_press(); // checks if a button is pressed along current activated row

				porA -> OUTCLR.reg = PORT_PA06;
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
				key_press();

				porA -> OUTCLR.reg = PORT_PA05;
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
				key_press();

				porA -> OUTCLR.reg = PORT_PA04;
				porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
				key_press();

				break;

		case 1:	// counting state to verify intended key press
				b = 0; //zero out checking variable b (keeps track of how many rows do not have anything pressed)
				// the displays are constantly refreshed so the numbers display while nothing is pressed
				porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06; // disable bottom three rows
				verify_press(); // checks if the pressed button is still pressed in current row and for how long

				porA -> OUTCLR.reg = PORT_PA06;
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
				verify_press();
		
				porA -> OUTCLR.reg = PORT_PA05;
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
				verify_press();
	
				porA -> OUTCLR.reg = PORT_PA04;
				porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
				verify_press();
		
				if (b == 4){ // if b equals 4 then that means no buttons are pressed in any row and go back to idle state
					state = 0;
					dcount = 0;
					b = 0;
				}
				break;

		case 2:	// processing state
				get_input(); // gets input from key press
				state = 3;
				break;

		case 3:	// counting state to check if button is released
				b = 0; // zero out checking variable b (keeps track of how many rows do not have anything pressed)
				// the displays are constantly refreshed so the numbers display while nothing is pressed
				porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06; // disable bottom three rows
				verify_release(); // checks if the pressed button is still pressed and for how long

				porA -> OUTCLR.reg = PORT_PA06;
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
				verify_release();

				porA -> OUTCLR.reg = PORT_PA05;
				porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
				verify_release();

				porA -> OUTCLR.reg = PORT_PA04;
				porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
				verify_release();

				dcount++;

				if (b == 4){ // if b = 4 then no buttons were pressed in any of the 4 rows and increment release counter
					dcount++;
				}
				else{
					dcount = 0; // if be is anything but 4 then something is still pressed and reset count
				}

				if (dcount > 10){ // counter for how long a button must be released before going back to idle state
					state = 0;
					dcount = 0;
				}

				break;
	}
	
	// for checking 1 or 0 is pressed or not?
	
	if (input1[0] == 1){
		state1 = 2; // if 1 is pressed change to speed up state
		input1[0] = 3; // proprietary value to keep condition from being satisfied multiple times
	}
	if (input1[0] == 0){ 
		state1 = 4; // if 0 is pressed change to slow down state
		input1[0] = 3; // proprietary value to keep condition from being satisfied multiple times
	}
	
	state_machine();
	seg_display();
}

void enable_interrupt(void)
{
	NVIC -> ISER[0] |= (1u << 15) | (1u << 4) |(1u << 16) | (1u << 17); // (table is on page 26)
	// tc2 interrupt is bit 15 and eic is bit 4 and tc3 interrupt  is bit 16)
	NVIC -> IP[1] = 0x00000000;				//EIC having the highest priority
	NVIC -> IP[3] = 0x40000000;
	NVIC -> IP[4] = 0x0000C080;
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
void enable_tc3(void){
	// table of registers on page 447
		//For TC2 (filter counter)
		PM->APBCMASK.reg |= 1u << 11;  	// PM_APBCMASK TC3 is in the bit 11 position (page 111)
		
		uint32_t temp= 0x14;   		// ID for tc2 is 0x14  (see table 14-2, page 92)
		temp |= 0<<8;         			//  Selection Generic clock generator 0
		GCLK->CLKCTRL.reg=temp;   		//  Setup in the CLKCTRL register
		GCLK->CLKCTRL.reg |= 0x1u << 14;    	// enable it.
		
	tc3 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc3 -> COUNT8.CTRLA.bit.PRESCALER = 0x7; // divide the clock by 1024
	tc3 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc3 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM

	tc3 -> COUNT8.PER.reg = 130; // set the period to 130 to get 60Hz sampling rate

	tc3 ->COUNT8.INTENSET.bit.OVF = 0x1;
	/*Enable TC*/
	tc3 -> COUNT8.CTRLA.reg |= 0x2;
}

void enable_tc4(void){
	enable_tc4_clocks();
	tc4 -> COUNT8.CTRLA.bit.MODE = 0x1; // configure the counter to be 8-bit
	tc4 -> COUNT8.CTRLA.bit.PRESCALER = 0x0; // divide the clock by 1
	tc4 -> COUNT8.CTRLA.bit.PRESCSYNC = 0x1; // set to PRESC to reset the counter on next prescaler clock
	tc4 -> COUNT8.CTRLA.bit.WAVEGEN = 0x2; // set the waveform generation operation to NPWM
	/* Write a suitable value to fix duty cycle and period.*/
	tc4 -> COUNT8.PER.reg = 255; // set the counter to count up to 255

	tc4 -> COUNT8.CTRLA.reg |= 0x2;
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


void verify_release(void){
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

	a = 0; // zero out checking variable a
	
	porA -> OUTSET.reg = PORT_PA19;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA19) {  // check that button is still pressed
		a = 1; // if button is pressed change checking variable a to 1
	}
	porA -> OUTSET.reg = PORT_PA18;
	porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA18) {  // check that button is still pressed
		a = 1;
	}
	porA -> OUTSET.reg = PORT_PA17;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA19 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA17) {  // check that button is still pressed
		a = 1;
	}
	porA -> OUTSET.reg = PORT_PA16;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA19;
	if (porA -> IN.reg & PORT_PA16) {  // check that button is still pressed
		a = 1;
	}
	if (a == 0){ // if checking variable a is 0 then no buttons were pressed so increment checking variable b
		b++;
	}
}

void verify_press(void){
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

	a = 0; // zero out checking variable a
	
	porA -> OUTSET.reg = PORT_PA19;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA19) {  // check that button is still pressed
		dcount++;
		a = 1;		// if button is pressed change checking variable a to 1
	}
	porA -> OUTSET.reg = PORT_PA18;
	porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA18) {  // check that button is still pressed
		dcount++;
		a = 1;
	}
	porA -> OUTSET.reg = PORT_PA17;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA19 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA17) {  // check that button is still pressed
		dcount++;
		a = 1;
	}
	porA -> OUTSET.reg = PORT_PA16;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA19;
	if (porA -> IN.reg & PORT_PA16) {  // check that button is still pressed
		dcount++;
		a = 1;
	}
	if (a == 0){ // if no buttons were pressed in this row increment checking variable b
		b++;
	}
	if (dcount > 10){ // counter for how long a button must be pressed
		state = 2;
	}
	
	return;
}

void key_press(void){
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

	porA -> OUTSET.reg = PORT_PA19;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA19){ //change state to 1 if any button is pressed
		state = 1;
	}
	porA -> OUTSET.reg = PORT_PA18;
	porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA18){ //change state to 1 if any button is pressed
		state = 1;
	}
	porA -> OUTSET.reg = PORT_PA17;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA19 | PORT_PA16;
	if (porA -> IN.reg & PORT_PA17){ //change state to 1 if any button is pressed
		state = 1;
	}
	porA -> OUTSET.reg = PORT_PA16;
	porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA19;
	if (porA -> IN.reg & PORT_PA16){ //change state to 1 if any button is pressed
		state = 1;
	}
	else{
		dcount = 0; // zero out counter
	}
	return;
}

void get_input(void){
	Port *ports = PORT_INSTS; //command to use port registers
	PortGroup *porA = &(ports->Group[0]); //introduce port groups A

	porA -> DIRSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA05 | PORT_PA04;

	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

		porA -> OUTSET.reg = PORT_PA06 | PORT_PA05 | PORT_PA04; //First row
		porA -> OUTCLR.reg = PORT_PA07;
		porA -> OUTSET.reg = PORT_PA19;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA19) { //Pushed 1
			while (porA -> IN.reg & PORT_PA19) {seg_display();}
			input1[0] = 1; // sends pressed number to an input array that will be used in the seg_display function
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA05; //Fourth row
		porA -> OUTCLR.reg = PORT_PA04;
		porA -> OUTSET.reg = PORT_PA18;
		porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA18) { //Pushed 0
			while (porA -> IN.reg & PORT_PA18) {seg_display();}
			input1[0] = 0;
		}
}