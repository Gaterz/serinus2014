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
double Odo_angle=ANGLE_INITIAL;
double Varia_x_f=0.0;
double Varia_y_f=0.0;
///////////////////////////////////////////////////////////////////////////
void Gestion_Odometrie_HL(signed long Delta_Tick_droit,signed long Delta_Tick_gauche)
{
	//Vars////////////////////////////////////////////////////////////
	double Delta_Distance;
	double Delta_angle;

	signed long Varia_x;
	signed long Varia_y;
	//Calculs delta position et angle/////////////////////////////////
	Delta_Distance	=(double)(Delta_Tick_gauche + Delta_Tick_droit)/2.0;
	Delta_angle		=(double)(Delta_Tick_gauche - Delta_Tick_droit)/2.0;
	//Calculs nouvelle position///////////////////////////////////////
	Odo_angle+=(double)(Delta_angle/ENTRAXE_TICK);

	Varia_x_f+=(double)(Delta_Distance*cos(Odo_angle));
	Varia_y_f+=(double)(Delta_Distance*sin(Odo_angle));

	Varia_x=(long)Varia_x_f;
	Varia_y=(long)Varia_y_f;

	Varia_x_f-=Varia_x;
	Varia_y_f-=Varia_y;

	Odo_pos_x+=Varia_x;
	Odo_pos_y+=Varia_y;
	//Normalisation de l'angle////////////////////////////////////////
	if(Odo_angle>ODO_ANGLE_MAX)
	{
		Odo_angle-=2*ODO_PI;
	}
	if(Odo_angle<ODO_ANGLE_MIN)
	{
		Odo_angle+=2*ODO_PI;
	}
}
