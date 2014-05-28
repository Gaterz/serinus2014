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
//unsigned int N_element=0;
void addElement(long x_cm, long y_cm , unsigned int id)
{
	long x=x_cm*CM_TICK_RATIO;
	long y=y_cm*CM_TICK_RATIO;
	Coord[id].x=x;
	Coord[id].y=y;
	//Coord[N_element].ang=ang;
	//N_element++;
}
void addElement_rouge()
{
	//addElement(1100, 400 , 0.0); //ID0 Triangle1
			//	X	 Y
	addElement(600, 230 , DOT_SORTIE);
	addElement(800, 600 , DOT_TRI1AP);
	addElement(1100, 600 , DOT_TRI1REN);
	addElement(1350, 700 , DOT_M1_E1);
	addElement(1350, 2100 , DOT_M1_E2);
	addElement(1400, 2100 , DOT_TRI4_2AP);
	addElement(1400, 700 , DOT_TRI4_2REN);

	addElement(600, 600 , DOT_M2_E1);
	addElement(600, 1350 ,DOT_M2_E2);
	addElement(200, 1350 ,DOT_FRESQUE_AP);

	addElement(1100, 650 ,DOT_T1_AP);
	addElement(1100, 900 ,DOT_T1_ACT);

	addElement(1350, 2000 ,DOT_T2_AP);
	addElement(1100, 2100 ,DOT_T2_ACT);

}
void addElement_jaune()
{
	addElement(600, 3000-230 , DOT_SORTIE);
	addElement(800, 3000-600 , DOT_TRI1AP);
	addElement(1100, 3000-600 , DOT_TRI1REN);
	addElement(1350, 3000-700 , DOT_M1_E1);
	addElement(1350, 3000-2100 , DOT_M1_E2);
	addElement(1400, 3000-2100 , DOT_TRI4_2AP);
	addElement(1400, 3000-700 , DOT_TRI4_2REN);

	addElement(600, 3000-600 , DOT_M2_E1);
	addElement(600, 3000-1350 ,DOT_M2_E2);
	addElement(200, 3000-1350 ,DOT_FRESQUE_AP);

	addElement(1100, 3000-650 ,DOT_T1_AP);
	addElement(1100, 3000-900 ,DOT_T1_ACT);

	addElement(1350, 3000-2000 ,DOT_T2_AP);
	addElement(1100, 3000-2100 ,DOT_T2_ACT);
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
		addElement_jaune();
	}
	else
	{
		LED_JAUNE=1;
		LED_ROUGE=1;
	}
}
