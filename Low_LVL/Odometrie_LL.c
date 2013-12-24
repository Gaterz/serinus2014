/**************************Odometrie_LL.c*********************************************
Auteur : Julien MAURAT
Date : 24 déc. 2013
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
static signed long Odometrie_last_tick_d = 0;
static signed long Odometrie_last_tick_g = 0;
void Gestion_Odometrie_LL(signed long Tick_droit,signed long Tick_gauche)
{
	signed long Delta_Tick_droit=Tick_droit-Odometrie_last_tick_d;
	signed long Delta_Tick_gauche=Tick_gauche-Odometrie_last_tick_g;
	Odometrie_last_tick_d=Tick_droit;
	Odometrie_last_tick_g=Tick_gauche;
	Gestion_Odometrie_HL(Delta_Tick_droit,Delta_Tick_gauche);
}
