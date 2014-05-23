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
	switch(Step)
		{
		case 0:
			setParam(act_TASK, addTask(move_systask,MOVE_SYSTASK_TYPE, 1, 0));
			addTask(move_systask,MOVE_SYSTASK_TYPE, 1, 1);
			addTask(move_systask,MOVE_SYSTASK_TYPE, 1, 2);
			addTask(move_systask,MOVE_SYSTASK_TYPE, 1, 3);
			setStep(1);
			break;
		case 1:
			startTask(Params);
			setStep(2);
			break;
		case 2:
			break;
		}

}

long move_systask_coordx[40];
long move_systask_coordy[40];
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
		k=move_to(move_systask_coordx[Params],move_systask_coordy[Params]);
		if(k==DEPLACEMENT_ARRET)
		{
			endTask();
			//runNextType();
		}
		break;
	}
}
unsigned int n_Move_Task=0;

int Add_move_task(signed long x,signed long y)
{
	int tID;
	move_systask_coordx[n_Move_Task]=x;
	move_systask_coordy[n_Move_Task]=y;
	addTask(&move_systask,MOVE_SYSTASK_TYPE, 1, n_Move_Task);
	n_Move_Task++;
	return tID;
}
