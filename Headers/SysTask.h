/*
 * SysTask.h
 *
 *  Created on: 9 mai 2014
 *      Author: Julien
 */

#ifndef SYSTASK_H_
#define SYSTASK_H_
void move_systask(unsigned char Step, unsigned int Params);
void match_systask(unsigned char Step, unsigned int Params);
void deplacement_systask(unsigned char Step, unsigned int Params);
int Add_move_task_coord(unsigned int dot_id,unsigned char backward);
int Add_move_task(signed long x,signed long y,unsigned char backward);

#endif /* SYSTASK_H_ */
