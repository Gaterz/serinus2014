/**************************Identification.c*********************************************
Auteur : Julien MAURAT
Date : 17 févr. 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
void Identification_entraxe()
{
	long i=0;
	Mode_Asserv(MODE_PI);
	Asserv_Cons_distance=15000;
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);


	Mode_Asserv(MODE_P);
	while(n_tour<2||Odo_angle<0)
	{
		Asserv_Cons_angle=Odo_angle+0.4+n_tour*3.14159265*2;
		//set_Asserv_angle_abs(Odo_angle+0.4);
	}
	Mode_Asserv(MODE_PI);
	Asserv_Cons_angle=3.14159265*2*2;
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	Asserv_Cons_distance=-500;
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	for(i=0;i<2000000;i++);
	Mode_Asserv(MODE_STOP);
	while(1)
	{
		printString("odo_angle :");
		printLongVal(Odo_angle*1000);//-2147483647);
		UART0_Sendchar('\n');
		for(i=0;i<2000000;i++);
			for(i=0;i<2000000;i++);
			for(i=0;i<2000000;i++);
			for(i=0;i<2000000;i++);
	}

}
