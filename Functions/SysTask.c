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
			setParam(act_TASK,Add_move_task(debug_dest_x,debug_dest_y));
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
int match_systask_id[10];
void match_systask(unsigned char Step, unsigned int Params)
{
	static char i=0;
	switch(Step)
		{
		case 0:
			match_systask_id[0]=Add_move_task_coord(DOT_SORTIE);
			match_systask_id[1]=Add_move_task_coord(DOT_TRI1AP);
			match_systask_id[2]=Add_move_task_coord(DOT_TRI1REN);
			match_systask_id[3]=Add_move_task_coord(DOT_M1_E1);
			match_systask_id[4]=Add_move_task_coord(DOT_M1_E2);
			match_systask_id[5]=Add_move_task_coord(DOT_TRI4_2AP);
			match_systask_id[6]=Add_move_task_coord(DOT_TRI4_2REN);

			setStep(1);
			break;
		case 1:
			startTask(match_systask_id[i]);
			setStep(2);
			break;
		case 2:
			if(getTaskState(match_systask_id[i])==TASK_STATE_ENDED)
			{
				i++;
				if(i==2)
				{
					AX12[0]=180;
				}
				else
				{
					AX12[0]=0;
				}
				if(i==6)
				{
					AX12[3]=180;
				}
				else
				{
					AX12[3]=0;
				}
				if(i==7)
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
		k=move_to(move_systask_coordx[Params],move_systask_coordy[Params],0);
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
	tID=addTask(&move_systask,MOVE_SYSTASK_TYPE, 1, n_Move_Task);
	n_Move_Task++;
	return tID;
}
int Add_move_task_coord(unsigned int dot_id)
{
	return Add_move_task(Coord[dot_id].x,Coord[dot_id].y);
}
