////////////////////////////////////////////////////////////////////////////////////// 
////	Lab 2 - Digital To Analog Converter 
////		-SAMPLE CODE DOES NOT WORK-
////			- insert variables into appropriate registers
////			- set up DAC pointer (similar to port_inst setup)
//////////////////////////////////////////////////////////////////////////////////////

#include <asf.h>
#include <math.h>

void Simple_Clk_Init(void);
void configure_dac(void);
void configure_dac_clock(void);
//initialize the DAC pointer
Dac *dac = DAC;
volatile int sinarr[147] = {0}; // array to store 147 sine wave values

int main(void)
{
	Simple_Clk_Init();
	configure_dac_clock();
	configure_dac();
	int i;
	double x;
	//We used the math header file to get access to the sin() function
	for(i = 0; i < 147; i++){ // generate the sine wave and store it in the array "sinarr" with 147 sample points
		x = (2 * 3.14 * i / 147);
		sinarr[i] = ((sin(x) + 1)*0.5)*1023;
	}

	i = 0; // reset array value

	while (1) {

				/* Wait until the synchronization is complete */
		while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {
		};
				
				/* Write the new value to the DAC DATA register */
				dac -> DATA.reg = sinarr[i]; // send each element of the array one by one to the data register of the DAC
				i++;
				if(i > 146){i = 0;} // reset the array value to first 
	}

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


	while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {
		/* wait until the synchronization is complete */
	}

	/* Set reference voltage with CTRLB */ // Page 550
		dac -> CTRLB.bit.REFSEL = 0x1; // set reference voltage to AVcc, Vcc is 3.3V

	while (dac -> STATUS.reg & DAC_STATUS_SYNCBUSY) {
		/* Wait until the synchronization is complete */
	}

	/* Enable the module with CTRLA */
		dac -> CTRLA.reg= 0x2; // set the enable bit (bit[1]) of the CTRLA register
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
