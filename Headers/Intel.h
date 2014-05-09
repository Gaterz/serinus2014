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
#define TASK_STATE_DELAYED 2
#define TASK_STATE_ENDED 3
#define TASK_STATE_CANCEL 4
#define TASK_STATE_NONE 5
///////////INTEL STATES
#define INTEL_STATE_STOP 0
#define INTEL_STATE_HALT 1
#define INTEL_STATE_PAUSE 2
#define INTEL_STATE_START 3
#define INTEL_STATE_RUN 4
///////////TASK TYPES
#define TASK_MOVE 0

void initIntel();
void runTasks();
void addTask(void (*Task)(unsigned char Step, unsigned int Params),unsigned char type, char n_run, unsigned int param);
void runNextType();
int getNextType();
void startTask(int id);
void stopTask(int id);
void endTask();
void setStep(unsigned char step);
#endif /* INTEL_H_ */
