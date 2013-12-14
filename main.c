/**********************************************************
                  Header files
 **********************************************************/

#include "main.h"

/**********************************************************
                       MAIN
**********************************************************/

int	main (void) {

											// loop counter (stack variable)

	// Initialize the system
	Initialize();
	initBlinkled();


	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();
		printString("hello world 2!");
	}
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
