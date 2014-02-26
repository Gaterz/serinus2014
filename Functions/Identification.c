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
signed int tableau_identif[1000];
signed int temp_i=0;
signed int temp_dst=0;
void Identification_constante_temps_lineaire()
{
	int i;
	while(temp_i<200)
	{
		if(temp_i<100)
		{
			Asserv_Cons_distance=5000+temp_dst;
			FLAG_IT_1MS=1;
			while(FLAG_IT_1MS==1);
		}
		else
		{
			Asserv_Cons_distance=6500+temp_dst;
			FLAG_IT_1MS=1;
			while(FLAG_IT_1MS==1);
		}
	}
	Mode_Asserv(MODE_STOP);
	while(1)
	{
		for(i=0;i<200;i++)
		{
			printLongVal(tableau_identif[i]);//2147483647);
			printString(",");

		}
		UART0_Sendchar('\n');
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);
		for(i=0;i<2000000;i++);

	}

}
