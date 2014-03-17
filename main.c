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
	char x=0;
	char y=0;
	char dist=0;
	char x_last=0;
	init_global();
	Mode_Asserv(MODE_STOP);
	CANinit_HW();
	Asserv_Cons_angle=0;
	canMsgType Msg1 ={
			1,
			1,
			0x44,
			0x0
	};
	// endless loop to toggle the red  LED P0.30
	while (1)
	{
		//blinkled();
		if(CANReceiveMessage(&Msg1)==1)
		{
			dist=Msg1.dataL&0xFF;
			x=(Msg1.dataL>>8)&0xFF;
			y=(Msg1.dataL>>16)&0xFF;
			if(x_last != x)
			{
				x_last=x;
				printString("x");
				UART0_Sendchar(x);//2147483647);
				UART0_Sendchar(y);//-2147483647);
				UART0_Sendchar(dist);//2147483647);
			}
		}

		//Asserv_Cons_distance = 15000;

		/*phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(20000,0);
		}while(k!=DEPLACEMENT_ARRET);
		phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(20000,20000);
		}while(k!=DEPLACEMENT_ARRET);
		phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(0,20000);
		}while(k!=DEPLACEMENT_ARRET);
		phase_deplacement=DEPLACEMENT_DEBUT;
		do
		{
			k=move_to(100,100);
		}while(k!=DEPLACEMENT_ARRET);

		*/

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

