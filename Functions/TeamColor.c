/**************************TeamColor.c*********************************************
Auteur : Julien MAURAT
Date : 24 mai 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
typedef struct {
	long x;
	long y;
	float ang;
}CoordSys;
CoordSys Coord_Jaune[50];
CoordSys Coord_Rouge[50];
CoordSys *Coord[50];
unsigned int act_Team=TEAM_NONE;
unsigned int N_element_Jaune=0;
unsigned int N_element_Rouge=0;
void addElement(long x, long y , float ang, unsigned char Team)
{
	if(Team==TEAM_JAUNE)
	{
		Coord_Jaune[N_element_Jaune].x=x;
		Coord_Jaune[N_element_Jaune].y=y;
		Coord_Jaune[N_element_Jaune].ang=ang;
		N_element_Jaune++;
	}
	else if(Team==TEAM_ROUGE)
	{
		Coord_Rouge[N_element_Rouge].x=x;
		Coord_Rouge[N_element_Rouge].y=y;
		Coord_Rouge[N_element_Rouge].ang=ang;
		N_element_Rouge++;
	}
}
void selectTeam()
{
	if(INTERUPTEUR_ROUGE==1)
	{
		LED_ROUGE=1;
		*Coord=Coord_Rouge;
		act_Team=TEAM_ROUGE;
	}
	else if(INTERUPTEUR_JAUNE==1)
	{
		LED_JAUNE=1;
		*Coord=Coord_Jaune;
		act_Team=TEAM_JAUNE;
	}
	else
	{
		LED_JAUNE=1;
		LED_ROUGE=1;
	}
}
