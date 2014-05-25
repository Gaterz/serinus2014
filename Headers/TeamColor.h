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
extern unsigned int act_Team;
void addElement(long x, long y , float ang, unsigned char Team);
void selectTeam();
#endif /* TEAMCOLOR_H_ */
