/**************************TeamColor.c*********************************************
Auteur : Julien MAURAT
Date : 24 mai 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"

CoordSys Coord[50];
unsigned int act_Team=TEAM_NONE;
unsigned int N_element=0;
void addElement(long x_cm, long y_cm , float ang)
{
	long x=x_cm*CM_TICK_RATIO;
	long y=y_cm*CM_TICK_RATIO;
	Coord[N_element].x=x;
	Coord[N_element].y=y;
	Coord[N_element].ang=ang;
	N_element++;
}
void addElement_rouge()
{
	//addElement(1100, 400 , 0.0); //ID0 Triangle1
	addElement(600, 230 , 0.0);//id0 sortie
	addElement(800, 600 , 0.0); //ID1 approche triangle1
	addElement(1100, 600 , 0.0); //ID2 renverssement triangle1
	addElement(1350, 700 , 0.0); //ID3 prepa ligne droite
	addElement(1350, 2100 , 0.0); //ID4 ligne droite
	addElement(1400, 2100 , 0.0); //ID5 ligne droite
	addElement(1400, 700 , 0.0); //ID6 ligne droite
}
void addElement_jaune()
{
	addElement(100, 140 , 0.0);

	addElement(100, 140 , 0.0);
}
void selectTeam()
{
	if(INTERUPTEUR_ROUGE==1)
	{
		LED_ROUGE=1;
		LED_JAUNE=0;
		//*Coord=Coord_Rouge;
		act_Team=TEAM_ROUGE;
		addElement_rouge();
	}
	else if(INTERUPTEUR_JAUNE==1)
	{
		LED_JAUNE=1;
		LED_ROUGE=0;
		//*Coord=Coord_Jaune;
		act_Team=TEAM_JAUNE;
	}
	else
	{
		LED_JAUNE=1;
		LED_ROUGE=1;
	}
}
