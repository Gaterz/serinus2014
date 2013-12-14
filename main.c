/* *********************************************************
               Function declarations
  ********************************************************* */

void Initialize(void);
void feed(void);
void init_UART0(void);
void blinkled(void);

void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

/**********************************************************
                  Header files
 **********************************************************/
#include "LPC22xx.h"

/**********************************************************
                       MAIN
**********************************************************/

int	main (void) {

											// loop counter (stack variable)

	// Initialize the system
	Initialize();

	// set io pins for led P0.30
	PINSEL1 &= 0xC0FFFFFF;  // configure pin as GPIO (default is analogue input)
	IO0DIR = 0x40000000;	// pin P0.30 is an output, everything else is input after reset
	IO0SET =  0x40000000;	// led off
	IO0CLR =  0x40000000;	// led on

	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();
	}
}



/**********************************************************
                      Initialize
**********************************************************/

#define PLOCK 0x400

void Initialize(void)  {

	// Setting Multiplier and Divider values
  	PLLCFG=0x23;
  	feed();

	// Enabling the PLL */
	PLLCON=0x1;
	feed();

	// Wait for the PLL to lock to set frequency
	while(!(PLLSTAT & PLOCK)) ;

	// Connect the PLL as the clock source
	PLLCON=0x3;
	feed();

	// Enabling MAM and setting number of clocks used for Flash memory fetch (4 cclks in this case)
	MAMCR=0x2;
	MAMTIM=0x4;

	// Setting peripheral Clock (pclk) to System Clock (cclk)
	VPBDIV=0x1;

	init_UART0();
}
void init_UART0(void)
{
	PINSEL0 |= 0x00000005;
	//UART0_LCR|=0x80;//Enable latch
	UART0_FCR=0b00000111;
	UART0_LCR=0b10000011;//Enable latch
	UART0_DLL=96;
	UART0_DLM=0;
	//Enable FIFO
	UART0_LCR=0b00000011;//8-bit no control 1 stop
	//UART0_LCR&=0b01111111;//clear latch
	UART0_THR='E';
}

void feed(void)
{
  PLLFEED=0xAA;
  PLLFEED=0x55;
}






/*  Stubs for various interrupts (may be replaced later)  */
/*  ----------------------------------------------------  */

void IRQ_Routine (void) {
	while (1) ;
}

void FIQ_Routine (void)  {
	while (1) ;
}


void SWI_Routine (void)  {
	while (1) ;
}


void UNDEF_Routine (void) {
	while (1) ;
}










