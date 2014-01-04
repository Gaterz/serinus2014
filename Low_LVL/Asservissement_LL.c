/**************************Asservissement_LL.c*********************************************
Auteur : Julien MAURAT
Date : 14 déc. 2013
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
void Gestion_Asserv_LL(signed long Tick_droit,signed long Tick_gauche,signed long* Cons_droite,signed long* Cons_gauche)
{
	signed long ordre_distance=0;
	signed long ordre_angle=0;

	if(get_Mode_Asserv()!=MODE_STOP)
	{
	//Appel du HL//////////////////////////////////////////////////////////
	Gestion_Asserv_HL(Tick_droit,Tick_gauche,&ordre_distance,&ordre_angle);
	*Cons_droite=ordre_distance-ordre_angle;
	*Cons_gauche=ordre_distance+ordre_angle;
	//Normalisation des conssignes/////////////////////////////////////////
	if(*Cons_droite>10000) *Cons_droite=10000;
	if(*Cons_droite<-10000) *Cons_droite=-10000;
	if(*Cons_gauche>10000) *Cons_gauche=10000;
	if(*Cons_gauche<-10000) *Cons_gauche=-10000;
	}

}
