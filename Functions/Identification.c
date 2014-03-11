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
	static int j=0;
	while(temp_i<400)
	{
		if(temp_i<200 && j==0)
		{
			controlMotor1_invert(7000);
			controlMotor2_invert(7000);
			j=1;
			//Asserv_Cons_distance=0;
			//FLAG_IT_1MS=1;
			//while(FLAG_IT_1MS==1);
		}
		else if(j==1 && temp_i>=200)
		{
			controlMotor1_invert(9000);
			controlMotor2_invert(9000);
			j=2;
			//Asserv_Cons_distance=5000;
			//FLAG_IT_1MS=1;
			//while(FLAG_IT_1MS==1);
		}
		/*else if(j==2 && temp_i>=400)
				{
					controlMotor1_invert(9000);
					controlMotor2_invert(9000);
					j=3;
					//Asserv_Cons_distance=5000;
					//FLAG_IT_1MS=1;
					//while(FLAG_IT_1MS==1);
				}*/
	}
	controlMotor1_invert(-8000);
	controlMotor2_invert(-8000);
	while(temp_i<800)
		{

		}
	//Mode_Asserv(MODE_STOP);
	controlMotor1_invert(0);
	controlMotor2_invert(0);
	while(1)
	{
		for(i=0;i<400;i++)
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
