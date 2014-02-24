/**************************Odometrie_HL.c*********************************************
Auteur : Julien MAURAT
Date : 16 déc. 2013
Description : Fonction d'odométrie haut niveau
Constantes : Odo_pos_x,Odo_pos_y,Odo_angle, correspond a la position déterminé via l'odometrie
Fonctions : void Gestion_Odometrie_HL(...) : Prend le delta de chaque roue codeuse, calcul la variation
en angle, en x et en y puis les ajoute aux coordonée actuelles.
**************************************************************************************/
#include "../all_head.h"
#include <math.h>
///////////global_vars/////////////////////////////////////////////////////
signed long Odo_pos_x=POS_X_INITIALLE;
signed long Odo_pos_y=POS_Y_INITIALLE;
long double Odo_angle=ANGLE_INITIAL;
int n_tour=0;
///////////////////////////////////////////////////////////////////////////
void Gestion_Odometrie_HL(signed long Delta_Tick_droit,signed long Delta_Tick_gauche)
{
	//Vars////////////////////////////////////////////////////////////
	long double Delta_Distance;
	long double Delta_angle;
	//Calculs delta position et angle/////////////////////////////////
	Delta_Distance	=(Delta_Tick_gauche + Delta_Tick_droit)/2;
	Delta_angle		=(Delta_Tick_gauche - Delta_Tick_droit)/2;
	//Calculs nouvelle position///////////////////////////////////////
	Odo_angle+=(long double)(Delta_angle/ENTRAXE_TICK);
	Odo_pos_x+=(long double)(Delta_Distance*cos(Odo_angle));
	Odo_pos_y+=(long double)(Delta_Distance*sin(Odo_angle));
	//Normalisation de l'angle////////////////////////////////////////
	if(Odo_angle>ODO_ANGLE_MAX)
	{
		Odo_angle-=2*ODO_PI;
		n_tour++;
	}
	if(Odo_angle<ODO_ANGLE_MIN)
	{
		Odo_angle+=2*ODO_PI;
		n_tour--;
	}
}
