///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE DOES NOT COMPLETE LAB 1 PART 1, IT IS JUST AN EXAMPLE SO THAT YOU MAY UNDERSTAND THE CODE SYNTAX
// This project shows how to perform Port Control. 
// It demonstrates how to set a pin as an input as well as output pin. 
// We toggle the LED on the SAMD20 whenever the button SW0 on the SAMD20 is pressed.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Include header files for all drivers
#include <asf.h>

//Include void functions
void wait(int t);
void Simple_Clk_Init(void);
void get_input(void); // obtain user input from keypad
void display_idle(void); // refresh display while in the middle of getting user input
void seg_display(int display); // controls display output
void key_press(void); // checks if any key is pressed
void verify_press(void); // checks how long a button is pressed
void verify_release(void); // checks how long a buttkon is released

//global variables
volatile int dcount = 0; // counter for the debouncing circuit
volatile int count = 0;
volatile int state = 0;
volatile int i;
volatile int input[4] = {0, 0, 0, 0}; // array where user input is stored
int a, b; // variables used 

int main (void)
{
	//set micro-controller clock to 8Mhz
	Simple_Clk_Init();

	//sets the base address for the Port structure to PORT_INSTS or 0x41004400
	Port *ports = PORT_INSTS;
	
	//sets the group offset for the structure PortGroup in this case it is for group[0] or groupA
	// GroupA offset of 0x00				// GroupB offset of 0x80
	PortGroup *porA = &(ports->Group[0]);
	PortGroup *porB = &(ports->Group[1]);
	
	// Set the direction outputs for the 7-segment displays
	porA->DIRSET.reg = (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7);
	porB->DIRSET.reg = (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6);

	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

	while (1){
		switch(state){
			case 0:		// idle state
						// the displays are constantly refreshed so the numbers display while nothing is pressed
						porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06; // disable bottom three rows
						key_press(); // checks if a button is pressed along current activated row
						seg_display(input[0]); // display most significant digit
						wait(5); // add delay to lower frequency of display refreshes

						porA -> OUTCLR.reg = PORT_PA06;
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
						key_press();
						seg_display(input[1]);
						wait(5);

						porA -> OUTCLR.reg = PORT_PA05;
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
						key_press();
						seg_display(input[2]);
						wait(5);

						porA -> OUTCLR.reg = PORT_PA04;
						porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
						key_press();
						seg_display(input[3]);// display least significant digit
						wait(5); 

						break;

			case 1:		// counting state to verify intended key press
						b = 0; //zero out checking variable b (keeps track of how many rows do not have anything pressed)
						// the displays are constantly refreshed so the numbers display while nothing is pressed
						porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06; // disable bottom three rows
						verify_press(); // checks if the pressed button is still pressed in current row and for how long
						seg_display(input[0]); // display most significant digit
						wait(5); // add delay to lower frequency of display refreshes

						porA -> OUTCLR.reg = PORT_PA06;
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
						verify_press();
						seg_display(input[1]);
						wait(5);

						porA -> OUTCLR.reg = PORT_PA05;
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
						verify_press();
						seg_display(input[2]);
						wait(5);

						porA -> OUTCLR.reg = PORT_PA04;
						porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
						verify_press();
						seg_display(input[3]);// display least significant digit
						wait(5);

						if (b == 4){ // if b equals 4 then that means no buttons are pressed in any row and go back to idle state
							state = 0;
							dcount = 0;
							b = 0;
						}

						break;

			case 2:		// processing state
						get_input(); // gets input from key press
						state = 3;
						break;

			case 3:		// counting state to check if button is released
						b = 0; // zero out checking variable b (keeps track of how many rows do not have anything pressed)
						// the displays are constantly refreshed so the numbers display while nothing is pressed
						porA -> OUTCLR.reg = PORT_PA07; // activate top row of keys
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06; // disable bottom three rows
						verify_release(); // checks if the pressed button is still pressed and for how long
						seg_display(input[0]); // display most significant digit
						wait(5); // add delay to lower frequency of display refreshes

						porA -> OUTCLR.reg = PORT_PA06;
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
						verify_release();
						seg_display(input[1]);
						wait(5);

						porA -> OUTCLR.reg = PORT_PA05;
						porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
						verify_release();
						seg_display(input[2]);
						wait(5);

						porA -> OUTCLR.reg = PORT_PA04;
						porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
						verify_release();
						seg_display(input[3]);// display least significant digit
						wait(5);

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
	}
}

void verify_release(void){
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	PortGroup *porB = &(ports->Group[1]);
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
	PortGroup *porB = &(ports->Group[1]);
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
	PortGroup *porB = &(ports->Group[1]);
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

void display_idle(void){
	Port *ports = PORT_INSTS;
	PortGroup *porA = &(ports->Group[0]);
	PortGroup *porB = &(ports->Group[1]);
	porA->DIRSET.reg = (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7);
	porB->DIRSET.reg = (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6);

	porA -> OUTCLR.reg = PORT_PA07;
	porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA06;
	seg_display(input[0]); // display most significant digit
	wait(5);
	porA -> OUTCLR.reg = PORT_PA06;
	porA -> OUTSET.reg = PORT_PA04 | PORT_PA05 | PORT_PA07;
	seg_display(input[1]);
	wait(5);
	porA -> OUTCLR.reg = PORT_PA05;
	porA -> OUTSET.reg = PORT_PA04 | PORT_PA07 | PORT_PA06;
	seg_display(input[2]);
	wait(5);
	porA -> OUTCLR.reg = PORT_PA04;
	porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA06;
	seg_display(input[3]);// display least significant digit
	wait(5); // add delay to lower frequency of display refreshes
	return;
}

void seg_display(int display){
	Port *ports = PORT_INSTS;
	PortGroup *porB = &(ports->Group[1]);
	porB -> DIRSET.reg = PORT_PB06 | PORT_PB05 | PORT_PB04 | PORT_PB03 | PORT_PB02 | PORT_PB01 | PORT_PB00;
	if (display == 0){ // port outputs to display 0 on the 7-segment display
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB03 | PORT_PB04 | PORT_PB05;
		porB -> OUTSET.reg = PORT_PB06;
	}
	if (display == 1){
		porB -> OUTCLR.reg = PORT_PB01 | PORT_PB02 ;
		porB -> OUTSET.reg = PORT_PB00 | PORT_PB03| PORT_PB04 | PORT_PB05 | PORT_PB06;
	}
	if (display == 2){
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB03 | PORT_PB04 | PORT_PB06;
		porB -> OUTSET.reg = PORT_PB02 | PORT_PB05;
	}
	if (display == 3){
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB03 | PORT_PB06;
		porB -> OUTSET.reg = PORT_PB04 | PORT_PB05;
	}
	if (display == 4){
		porB -> OUTCLR.reg = PORT_PB01 | PORT_PB02 | PORT_PB05 | PORT_PB06;
		porB -> OUTSET.reg = PORT_PB00 | PORT_PB03 | PORT_PB04;
	}
	if (display == 5){
		porB -> OUTSET.reg = PORT_PB01 | PORT_PB04 | PORT_PB07;
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB02 | PORT_PB03 | PORT_PB05 | PORT_PB06;
	}
	if (display == 6){
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB02 | PORT_PB03 | PORT_PB04 | PORT_PB05 | PORT_PB06;
		porB -> OUTSET.reg = PORT_PB01;
	}
	if (display == 7){
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02;
		porB -> OUTSET.reg = PORT_PB03 | PORT_PB04 | PORT_PB05 | PORT_PB06;
	}
	if (display == 8){
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB03 | PORT_PB04 | PORT_PB05 | PORT_PB06;
	}
	if (display == 9){
		porB -> OUTCLR.reg = PORT_PB00 | PORT_PB01 | PORT_PB02 | PORT_PB05 | PORT_PB06;
		porB -> OUTSET.reg = PORT_PB03 | PORT_PB04;
	}
	return;
}

void get_input(void){
	Port *ports = PORT_INSTS; //command to use port registers
	PortGroup *porA = &(ports->Group[0]); //introduce port groups A
	PortGroup *porB = &(ports->Group[1]); //introduce port groups B

	porA -> DIRSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA05 | PORT_PA04;
	porB -> DIRSET.reg = PORT_PB06 | PORT_PB05 | PORT_PB04 | PORT_PB03 | PORT_PB02 | PORT_PB01 | PORT_PB00;

	porA -> DIRCLR.reg = PORT_PA19 | PORT_PA18 | PORT_PA17 | PORT_PA16;
	porA -> PINCFG[19].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[18].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[17].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	porA -> PINCFG[16].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;


	while(1){
		porA -> OUTSET.reg = PORT_PA06 | PORT_PA05 | PORT_PA04; //First row
		porA -> OUTCLR.reg = PORT_PA07;
		porA -> OUTSET.reg = PORT_PA19;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA19) { //Pushed 1
			if (i == 4) i = 0; // reset array pointer when max number is reached
			input[i] = 1; // sends pressed number to an input array that will be used in the seg_display function
			i++;
			while (porA -> IN.reg & PORT_PA19) {display_idle();} // waits until button is released and cycles through display in the meantime
		}

		porA -> OUTSET.reg = PORT_PA06 | PORT_PA05 | PORT_PA04; //First row
		porA -> OUTCLR.reg = PORT_PA07;
		porA -> OUTSET.reg = PORT_PA18;
		porA -> OUTCLR.reg = PORT_PA17 | PORT_PA19 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA18){ //Pushed 2
			if (i == 4) i = 0;
			input[i] = 2;
			i++;
			while (porA -> IN.reg & PORT_PA18) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA06 | PORT_PA05 | PORT_PA04; //First row
		porA -> OUTCLR.reg = PORT_PA07;
		porA -> OUTSET.reg = PORT_PA17;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA19 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA17) { //Pushed 3
			if (i == 4) i = 0;
			input[i] = 3;
			i++;
			while (porA -> IN.reg & PORT_PA17) {display_idle();}
		}


		porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA04; //Second row
		porA -> OUTCLR.reg = PORT_PA06;
		porA -> OUTSET.reg = PORT_PA19;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA19) { //Pushed 4
			if (i == 4) i = 0;
			input[i] = 4;
			i++;
			while (porA -> IN.reg & PORT_PA19) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA04; //Second row
		porA -> OUTCLR.reg = PORT_PA06;
		porA -> OUTSET.reg = PORT_PA18;
		porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA18) { //Pushed 5
			if (i == 4) i = 0;
			input[i] = 5;
			i++;
			while (porA -> IN.reg & PORT_PA18) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA05 | PORT_PA04; //Second row
		porA -> OUTCLR.reg = PORT_PA06;
		porA -> OUTSET.reg = PORT_PA17;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA19 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA17){ //Pushed 6
			if (i == 4) i = 0;
			input[i] = 6;
			i++;
			while (porA -> IN.reg & PORT_PA17) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA04; //Third row
		porA -> OUTCLR.reg = PORT_PA05;
		porA -> OUTSET.reg = PORT_PA19;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA19) { //Pushed 7
			if (i == 4) i = 0;
			input[i] = 7;
			i++;
			while (porA -> IN.reg & PORT_PA19) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA04; //Third row
		porA -> OUTCLR.reg = PORT_PA05;
		porA -> OUTSET.reg = PORT_PA18;
		porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA18) { //Pushed 8
			if (i == 4) i = 0;
			input[i] = 8;
			i++;
			while (porA -> IN.reg & PORT_PA18) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA04; //Third row
		porA -> OUTCLR.reg = PORT_PA05;
		porA -> OUTSET.reg = PORT_PA17;
		porA -> OUTCLR.reg = PORT_PA18 | PORT_PA19 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA17) { //Pushed 9
			if (i == 4) i = 0;
			input[i] = 9;
			i++;
			while (porA -> IN.reg & PORT_PA17) {display_idle();}
		}

		porA -> OUTSET.reg = PORT_PA07 | PORT_PA06 | PORT_PA05; //Fourth row
		porA -> OUTCLR.reg = PORT_PA04;
		porA -> OUTSET.reg = PORT_PA18;
		porA -> OUTCLR.reg = PORT_PA19 | PORT_PA17 | PORT_PA16;
		if (porA -> IN.reg & PORT_PA18) { //Pushed 0
			if (i == 4) i = 0;
			input[i] = 0;
			i++;
			while (porA -> IN.reg & PORT_PA18) {display_idle();}
		}
		break;
	}
	return;
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

//Simple Clock Initialization - Do Not Modify -//
void Simple_Clk_Init(void)
{
	/* Various bits in the INTFLAG register can be set to one at startup.
	   This will ensure that these bits are cleared */
	
	SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET |
			SYSCTRL_INTFLAG_DFLLRDY;
			
	system_flash_set_waitstates(0);  		//Clock_flash wait state =0

	SYSCTRL_OSC8M_Type temp = SYSCTRL->OSC8M;      	/* for OSC8M initialization  */

	temp.bit.PRESC    = 0;    			// no divide, i.e., set clock=8Mhz  (see page 170)
	temp.bit.ONDEMAND = 1;    			// On-demand is true
	temp.bit.RUNSTDBY = 0;    			// Standby is false
	
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
