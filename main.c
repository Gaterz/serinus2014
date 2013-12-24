/**********************************************************
                  Header files
 **********************************************************/

#include "main.h"

/**********************************************************
                       MAIN
**********************************************************/
int	main (void) {
	// loop counter (stack variable)
	//long c_droit=0;
	//long c_gauche=0;
	// Initialize the system
	Initialize();
	initBlinkled();
	initES_cod();
	resetCodeurs();
	InitTimer1();
	enableIRQ();

	Asserv_Cons_distance=500;
	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();

		//////////////////debug///////////////////////
		//testtimeval=TIMER1_TC;
				//Gestion_Asserv_HL(100,100,&c_droit,&c_gauche);
				//Asserv_Cons_distance=500;
				printString("X : ");
				printLongVal(Odo_pos_x);
				printString(" Y : ");
				printLongVal(Odo_pos_y);
				UART0_Sendchar('\n');
		//////////////////////////////////////////////
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
void start_tempo(void)//temporisation RAM
{
	int j;
	for(j=0;j<100000;j++);
	asm("b strrn");
}

