/**********************************************************
                  Header files
 **********************************************************/

#include "main.h"
extern signed int phase_deplacement;
/**********************************************************
                       MAIN
**********************************************************/
int	main (void) {
	// loop counter (stack variable)
	//long c_droit=0;
	//long c_gauche=0;
	int k=0;
	init_global();
	Mode_Asserv(MODE_PID);
	addTask(move_task,TASK_MOVE, 1, 0);
	addTask(move_task,TASK_MOVE, 1, 1);
	addTask(move_task,TASK_MOVE, 1, 2);
	addTask(move_task,TASK_MOVE, 1, 3);
	//Asserv_Cons_angle=0;
	//printString("AT+BAUD6");
	//UART0_Sendchar('\n');
	//while(1);
	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();
		runTasks();
		//Asserv_Cons_distance = 15000;

		/*phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(60000,0);
		}while(k!=DEPLACEMENT_ARRET);
		phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(60000,60000);
		}while(k!=DEPLACEMENT_ARRET);
		phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(0,60000);
		}while(k!=DEPLACEMENT_ARRET);
		phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(100,100);
		}while(k!=DEPLACEMENT_ARRET);*/



		/*
		//////////////////debug///////////////////////
		//testtimeval=TIMER1_TC;
				//Gestion_Asserv_HL(100,100,&c_droit,&c_gauche);
				//Asserv_Cons_distance=500;
				printString("X : ");
				printLongVal(Odo_pos_x);//2147483647);
				printString(" Y : ");
				printLongVal(Odo_pos_y);//-2147483647);
				UART0_Sendchar('\n');*/
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
	int j=0;
	for(j=0;j<100000;j++);
	asm("b strrn");
}

