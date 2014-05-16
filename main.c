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
	addTask(move_systask,TASK_MOVE, 1, 0);
	addTask(move_systask,TASK_MOVE, 1, 1);
	addTask(move_systask,TASK_MOVE, 1, 2);
	addTask(move_systask,TASK_MOVE, 1, 3);
	while (1)
	{
		//blinkled();
		runTasks();
		Routine_CAN();
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

