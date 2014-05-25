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
CoordSys Coord_game[2][50];
unsigned int N_element_g=0;
void addElement(long x, long y , float ang, unsigned char Team)
{
	Coord_game[Team][N_element_g].x=x;
	Coord_game[Team][N_element_g].y=y;
	Coord_game[Team][N_element_g].ang=ang;
	N_element_g++;
}
