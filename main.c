/**********************************************************
                  Header files
 **********************************************************/

#include "main.h"
extern signed int phase_deplacement;
/**********************************************************
                       MAIN
**********************************************************/
int	main (void) {
	init_global();
	Mode_Asserv(MODE_PID);

	while(FLAG_START==0)
	{

	}
	Intel_Start();
	while (1)
	{
		//blinkled();
		runTasks();
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
	int j=0;
	for(j=0;j<100000;j++);
	asm("b strrn");
}

