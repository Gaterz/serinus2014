/**************************Odometrie_HL.c*********************************************
Auteur : Julien MAURAT
Date : 16 déc. 2013
Description : Fonction d'odométries haut niveau
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
#include <math.h>
signed long Odo_pos_x=POS_X_INITIALLE;
signed long Odo_pos_y=POS_Y_INITIALLE;
long double Odo_angle=ANGLE_INITIAL;


void Gestion_Odometrie_HL(signed long Delta_Tick_droit,signed long Delta_Tick_gauche)
{
	long double Delta_Distance	=(Delta_Tick_droit + Delta_Tick_gauche)/2;
	long double Delta_angle		=(Delta_Tick_droit - Delta_Tick_gauche)/2;


	Odo_angle+=(long double)(Delta_angle/ENTRAXE_TICK);
	Odo_pos_x+=(long double)(Delta_Distance*cos(Odo_angle));
	Odo_pos_y+=(long double)(Delta_Distance*sin(Odo_angle));

}
