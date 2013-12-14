#include "all_head.h"
/**********************************************************
                      Initialize
**********************************************************/

#define PLOCK 0x400

void Initialize(void)
{

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

void feed(void)
{
  PLLFEED=0xAA;
  PLLFEED=0x55;
}
