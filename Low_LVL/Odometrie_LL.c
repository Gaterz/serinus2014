/**************************Odometrie_LL.c*********************************************
Auteur : Julien MAURAT
Date : 24 déc. 2013
Description : Fonctions de bas niveau de l'odométrie
Constantes : N/A
Fonctions : void Gestion_Odometrie_LL(...) : gestion bas-niveau de l'odometrie,
pour le moment calcul du delta des roues codeuses
**************************************************************************************/
#include "../all_head.h"
///////////static_vars/////////////////////////////////////////////////////
static signed long Odometrie_last_tick_d = 0;
static signed long Odometrie_last_tick_g = 0;
///////////////////////////////////////////////////////////////////////////
void Gestion_Odometrie_LL(signed long Tick_droit,signed long Tick_gauche)
{
	//Vars/////////////////////////////////////////////////////////////////
	signed long Delta_Tick_droit;
	signed long Delta_Tick_gauche;
	//Calcul delta/////////////////////////////////////////////////////////
	Delta_Tick_droit	=Tick_droit	-Odometrie_last_tick_d;
	Delta_Tick_gauche	=Tick_gauche-Odometrie_last_tick_g;
	Odometrie_last_tick_d=Tick_droit;
	Odometrie_last_tick_g=Tick_gauche;
	//Passage fonction HL//////////////////////////////////////////////////
	Gestion_Odometrie_HL(Delta_Tick_droit,Delta_Tick_gauche);
}
