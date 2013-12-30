/**************************Routine_1ms.c*********************************************
Auteur : Julien MAURAT
Date : 24 déc. 2013
Description : Routine appelée par l'interruption périodique
Constantes : N/A
Fonctions : void routine_1ms(void) : Vas gérer l'appel au diverses fonction d'odométrie
et d'asservissement
**************************************************************************************/
#include "../all_head.h"

void routine_1ms(void)
{
	//vars
	signed long Codeur_d=0;
	signed long Codeur_g=0;
	//gestion codeurs
	lectureCodeursSigned(&Codeur_d,&Codeur_g);
	//gestion odoetrie
	Gestion_Odometrie_LL(Codeur_d,Codeur_g);
	//gestion asserv
}
