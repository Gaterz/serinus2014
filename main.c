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
	int test_i=0;
	int state=0;
	Asserv_Cons_distance=10000;
	Mode_Asserv(MODE_PI);

	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		blinkled();
		if(Odo_pos_x>9500 && get_Mode_Asserv()==MODE_PI && state==0)
		{
			test_i++;
			if(test_i > 4)
			{
				Asserv_Cons_distance=0;
				test_i=0;
				state=1;


			}
		}
		if(Odo_pos_x<500 && get_Mode_Asserv()==MODE_PI && state==1)
				{
					test_i++;
					if(test_i > 4)
					{
						Asserv_Cons_distance=10000;
						test_i=0;
						state=0;
					}
				}

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

