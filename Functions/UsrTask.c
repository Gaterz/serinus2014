/**************************UsrTask.c*********************************************
Auteur : Julien MAURAT
Date : 9 mai 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
int fresque_systask_id[2];
void fresque_systask(unsigned char Step, unsigned int Params)
{
	//static timer=0;
	int i;
	switch(Step)
	{
	case 0:
		fresque_systask_id[0]=Add_move_task_coord(DOT_M2_E2,0);
		fresque_systask_id[1]=Add_move_task_coord(DOT_FRESQUE_AP,0);
		setStep(1);
		break;
	case 1:
		startTask(fresque_systask_id[0]);
		setStep(2);
		break;
	case 2:
		if(getTaskState(fresque_systask_id[0])==TASK_STATE_ENDED)
		{
			setStep(3);
			startTask(fresque_systask_id[1]);
		}
		break;
	case 3:
		if(getTaskState(fresque_systask_id[1])==TASK_STATE_ENDED)
		{
			FLAG_MANUAL=1;
			controlMotor1_invert(3500);
			controlMotor2_invert(3000);
			for(i=0;i<200;i++)
			{
				FLAG_IT_1MS=1;
				while(FLAG_IT_1MS==1)
				{
				}
			}
			FLAG_MANUAL=0;
			endTask();
		}
	break;
	}
}
int triangle24_systask_id[4];
void triangle24_systask(unsigned char Step, unsigned int Params)
{
	//static char i=0;
	switch(Step)
		{
		case 0:
			triangle24_systask_id[0]=Add_move_task_coord(DOT_M1_E1,0);
			triangle24_systask_id[1]=Add_move_task_coord(DOT_M1_E2,0);
			triangle24_systask_id[2]=Add_move_task_coord(DOT_TRI4_2AP,0);
			triangle24_systask_id[3]=Add_move_task_coord(DOT_TRI4_2REN,0);
			setStep(1);
			break;
		case 1:
			startTask(triangle24_systask_id[Params]);
			setStep(2);
			break;
		case 2:
			if(getTaskState(triangle24_systask_id[Params])==TASK_STATE_ENDED)
			{
				setParam(act_TASK, Params+1);
				if(getParam(act_TASK)==3)
				{
					AX12[3]=180;
				}
				else
				{
					AX12[3]=0;
				}
				if(getParam(act_TASK)==4)
				{
					endTask();
				}
				else
				{
					setStep(1);
				}
			}
			break;
		}
}
int triangle1_usrtask_id[2];
void triangle1_usrtask(unsigned char Step, unsigned int Params)
{
	//static char i=0;
	switch(Step)
		{
		case 0:

			triangle1_usrtask_id[0]=Add_move_task_coord(DOT_TRI1AP,0);
			triangle1_usrtask_id[1]=Add_move_task_coord(DOT_TRI1REN,0);
			setStep(1);
			break;
		case 1:
			startTask(triangle1_usrtask_id[Params]);
			setStep(2);
			break;
		case 2:
			if(getTaskState(triangle1_usrtask_id[Params])==TASK_STATE_ENDED)
			{
				setParam(act_TASK, Params+1);
				if(getParam(act_TASK)==1)
				{
					AX12[0]=180;
				}
				else
				{
					AX12[0]=0;
				}
				if(getParam(act_TASK)==2)
				{
					endTask();
				}
				else
				{
					setStep(1);
				}
			}
			break;
		}
}
int Torche1_usrtask_id[2];
void Torche1_usrtask(unsigned char Step, unsigned int Params)
{
	//static char i=0;
	switch(Step)
		{
		case 0:

			Torche1_usrtask_id[0]=Add_move_task_coord(DOT_T1_AP,0);
			Torche1_usrtask_id[1]=Add_move_task_coord(DOT_T1_ACT,1);
			setStep(1);
			break;
		case 1:
			startTask(Torche1_usrtask_id[Params]);
			setStep(2);
			break;
		case 2:
			if(getTaskState(Torche1_usrtask_id[Params])==TASK_STATE_ENDED)
			{
				setParam(act_TASK, Params+1);
				if(getParam(act_TASK)==1)
				{
					AX12[4]=255;
				}
				else
				{
					//AX12[4]=0;
				}
				if(getParam(act_TASK)==2)
				{
					endTask();
				}
				else
				{
					setStep(1);
				}
			}
			break;
		}
}

int Torche2_usrtask_id[2];
void Torche2_usrtask(unsigned char Step, unsigned int Params)
{
	//static char i=0;
	switch(Step)
		{
		case 0:

			Torche2_usrtask_id[0]=Add_move_task_coord(DOT_T2_AP,0);
			Torche2_usrtask_id[1]=Add_move_task_coord(DOT_T2_ACT,1);
			setStep(1);
			break;
		case 1:
			startTask(Torche2_usrtask_id[Params]);
			setStep(2);
			break;
		case 2:
			if(getTaskState(Torche2_usrtask_id[Params])==TASK_STATE_ENDED)
			{
				setParam(act_TASK, Params+1);
				if(getParam(act_TASK)==1)
				{
					AX12[4]=255;
				}
				else
				{
					//AX12[4]=0;
				}
				if(getParam(act_TASK)==2)
				{
					endTask();
				}
				else
				{
					setStep(1);
				}
			}
			break;
		}
}
