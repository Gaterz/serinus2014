/*
 * TeamColor.h
 *
 *  Created on: 24 mai 2014
 *      Author: Julien
 */

#ifndef TEAMCOLOR_H_
#define TEAMCOLOR_H_
#define TEAM_NONE 0
#define TEAM_JAUNE 1
#define TEAM_ROUGE 2
#define CM_TICK_RATIO 104
typedef struct {
	long x;
	long y;
	float ang;
}CoordSys;
extern CoordSys Coord[50];
extern unsigned int act_Team;
void addElement(long x_cm, long y_cm , unsigned int id);
void addElement_rouge();
void selectTeam();
#endif /* TEAMCOLOR_H_ */
