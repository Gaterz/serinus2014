/* *********************************************************
               Function declarations
  ********************************************************* */

void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

/**********************************************************
                  Header files
 **********************************************************/
#include "LPC22xx.h"
#include "Headers/Basic_blinkled.h"

/**********************************************************
                       MAIN
**********************************************************/

int	main (void) {

											// loop counter (stack variable)

	// Initialize the system
	Initialize();



	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();
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
