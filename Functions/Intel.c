/**************************Intel.c*********************************************
Auteur : Julien MAURAT
Date : 25 avr. 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"

///////////////////////////Task Pool
void (*Task_pool[N_MAX_TASK])(unsigned char Step, unsigned int Params);

///////////////////////////Task Attributes
///////////RUN/NORUN
unsigned char RUN[N_MAX_TASK];
///////////TASK STATE
unsigned char STATE[N_MAX_TASK];
///////////TASK STEP
unsigned char STEP[N_MAX_TASK];
///////////TASK TYPE
unsigned char TYPE[N_MAX_TASK];
///////////TASK N_RUN
char N_RUN[N_MAX_TASK];
///////////TASK PARAM
unsigned int PARAM[N_MAX_TASK];

//void* Attributes[N_TASK_ATTRIBUTES]={RUN,STATE,STEP,TYPE,N_RUN,PARAM};

///////////////////////////Intel Attributes
///////////INTEL_STATE
unsigned char INTEL_STATE=INTEL_STATE_STOP;

///////////N TASK
unsigned char N_Task=0;
///////////ACTUAL TASK
unsigned char act_TASK=0;
void initIntel()
{
	int i;
	for(i=0;i<N_MAX_TASK;i++)
	{
		RUN[i]=0;
		STATE[i]=TASK_STATE_NONE;
		STEP[i]=0;
		TYPE[i]=0;
		N_RUN[i]=-1;
		PARAM[i]=0;
	}
	RUN[0]=1;
}
void addTask(void (*Task)(unsigned char Step, unsigned int Params),unsigned char type, char n_run, unsigned int param)
{
	Task_pool[N_Task]=Task;
	STATE[N_Task]=TASK_STATE_NEW;
	N_RUN[N_Task]=n_run;
	PARAM[N_Task]=param;
	N_Task++;
}
void runTasks()
{
	int i;
	for(i=0;i<N_Task;i++)
	{
		if(RUN[i]==1 &&(N_RUN[i]==-1 || N_RUN[i] > 0))
		{
			act_TASK=i;
			(*Task_pool[i])(STEP[i],PARAM[i]);

		}

	}
}
void runNextType()
{
	int nextID=getNextType();
	if(nextID!=-1)
	{
		startTask(nextID);
	}
}
int getNextType()
{
	unsigned char actType=TYPE[act_TASK];
	int i;
	for(i=act_TASK+1;i<N_Task;i++)
	{
		if(TYPE[i]==actType)
		{
			return i;
		}
	}
	return -1;
}
void startTask(int id)
{
	STEP[id]=0;
	RUN[id]=1;
}
void stopTask(int id)
{
	RUN[id]=0;
}
void endTask()
{
	N_RUN[act_TASK]--;
	if(N_RUN[act_TASK]<-1)N_RUN[act_TASK]=-1;
}
void setStep(unsigned char step)
{
	STEP[act_TASK]=step;
}
