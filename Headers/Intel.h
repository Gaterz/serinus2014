/*
 * Intel.h
 *
 *  Created on: 25 avr. 2014
 *      Author: Julien
 */

#ifndef INTEL_H_
#define INTEL_H_

#define N_MAX_TASK 50
//#define N_TASK_ATTRIBUTES 6


///////////TASK STATE
//extern unsigned char STATE[];

///////////TASK TYPE
//extern unsigned char TYPE[];
///////////TASK N_RUN
//extern char N_RUN[];
///////////TASK PARAM
//extern unsigned int PARAM[];

///////////////////////////Intel Attributes
///////////ACTUAL TASK
extern unsigned char act_TASK;




///////////TASK STATES
#define TASK_STATE_NEW 0
#define TASK_STATE_TODO 1
#define TASK_STATE_RUNNING 2
#define TASK_STATE_DELAYED 3
#define TASK_STATE_ENDED 4
#define TASK_STATE_CANCEL 5
#define TASK_STATE_NONE 6
///////////INTEL STATES
#define INTEL_STATE_STOP 0
#define INTEL_STATE_HALT 1
#define INTEL_STATE_PAUSE 2
#define INTEL_STATE_START 3
#define INTEL_STATE_RUN 4
///////////TASK TYPES
#define FRESQUE_SYSTASK 3
#define TRIANGLE24_SYSTASK 4
#define TRIANGLE1_USRTASK 5
#define TORCHE1_USRTASK 6

///////////SYS TASK
#define MATCH_SYSTASK_TYPE 0
#define DEPLACEMENT_SYSTASK_TYPE 1
#define MOVE_SYSTASK_TYPE 2

void initIntel();
void runTasks();
unsigned int addTask(void (*Task)(unsigned char Step, unsigned int Params),unsigned char type, char n_run, unsigned int param);
void runNextType();
int getNextType();
void startTask(int id);
void PauseTask(int id);
void endTask();
void setStep(unsigned char step);
void setParam(int id, unsigned int param);
unsigned int getParam(int id);
unsigned char getTaskState(int id);
void Intel_Start();
#endif /* INTEL_H_ */
