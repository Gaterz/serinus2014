/**********************************************************
                  Header files
 **********************************************************/

#include "main.h"
//extern signed int phase_deplacement;
/**********************************************************
                       MAIN
**********************************************************/
int	main (void) {
	init_global();
	Mode_Asserv(MODE_PID);
	Intel_Start();



	while(act_Team==TEAM_NONE)
	{
		selectTeam();
	}
	//self_pos_rouge();
	while(FLAG_START==0)
		{
		if(INTERUPTEUR_JACK==1)
		{
			FLAG_START=1;
		}
		}
	while (!FLAG_TIMER_EN || Timer_Match <=9000)
	{
		//blinkled();
		//
		runTasks();
	}
	Mode_Asserv(MODE_STOP);
	while(1)
	{

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

