/**************************SysTask.c*********************************************
Auteur : Julien MAURAT
Date : 9 mai 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
void deplacement_systask(unsigned char Step, unsigned int Params)
{

}

void match_systask(unsigned char Step, unsigned int Params)
{

}

int tmp_coordx[5]={40000,40000,0,100};
int tmp_coordy[5]={0,40000,40000,100};
void move_systask(unsigned char Step, unsigned int Params)
{
	unsigned char k;
	switch(Step)
	{
	case 0 :
		phase_deplacement=DEPLACEMENT_DEBUT;
		setStep(1);
		break;
	case 1 :
		k=move_to(tmp_coordx[Params],tmp_coordy[Params]);
		if(k==DEPLACEMENT_ARRET)
		{
			endTask();
			runNextType();
		}
		break;
	}
}