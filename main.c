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
	init_global();
	//Asserv_Cons_distance=10000;
	//Asserv_Cons_angle=-1.57;
	Mode_Asserv(MODE_PI);

	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();
		move_to(1000,1000);



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
	int j;
	for(j=0;j<100000;j++);
	asm("b strrn");
}

