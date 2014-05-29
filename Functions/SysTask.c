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
	switch(Step)
	{
	case 0:
		if(debug_start_move==1)
		{
			setParam(act_TASK,Add_move_task(debug_dest_x,debug_dest_y,0));
			startTask(getParam(act_TASK));
		}
		setStep(1);
		break;
	case 1:
		if(getTaskState(Params)==TASK_STATE_ENDED)
		{
			debug_start_move=0;
			setStep(0);
		}
		break;
	}
}
int match_systask_id[4];
void match_systask(unsigned char Step, unsigned int Params)
{
	//static char i=0;
	switch(Step)
		{
		case 0:
			match_systask_id[0]=Add_move_task_coord(DOT_SORTIE,0);
			match_systask_id[2]=addTask(&Torche1_usrtask,TORCHE1_USRTASK,1, 0);
			match_systask_id[1]=addTask(&triangle1_usrtask,TRIANGLE1_USRTASK,1, 0);
			//match_systask_id[2]=addTask(&triangle24_systask,TRIANGLE24_SYSTASK,1, 0);
			//match_systask_id[3]=addTask(&fresque_systask,FRESQUE_SYSTASK,1, 0);
			setStep(1);
			break;
		case 1:
			startTask(match_systask_id[Params]);
			setStep(2);
			break;
		case 2:
			if(getTaskState(match_systask_id[Params])==TASK_STATE_ENDED)
			{
				setParam(act_TASK, Params+1);
				if( getParam(act_TASK)==3)
				{
					setStep(3);
				}
				else
				{
					setStep(1);
				}
				//if(i>3)i=0;

			}
			break;
		case 3:
			break;
		}
}

long move_systask_coordx[40];
long move_systask_coordy[40];
unsigned char move_systask_backward[40];
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
		k=move_to(move_systask_coordx[Params],move_systask_coordy[Params],move_systask_backward[Params]);
		if(k==DEPLACEMENT_ARRET)
		{
			endTask();
			//runNextType();
		}
		break;
	}
}
unsigned int n_Move_Task=0;

int Add_move_task(signed long x,signed long y,unsigned char backward)
{
	int tID;
	move_systask_coordx[n_Move_Task]=x;
	move_systask_coordy[n_Move_Task]=y;
	move_systask_backward[n_Move_Task]=backward;
	tID=addTask(&move_systask,MOVE_SYSTASK_TYPE, 1, n_Move_Task);
	n_Move_Task++;
	return tID;
}
int Add_move_task_coord(unsigned int dot_id,unsigned char backward)
{
	return Add_move_task(Coord[dot_id].x,Coord[dot_id].y,backward);
}
