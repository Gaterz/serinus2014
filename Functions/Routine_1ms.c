/**************************Routine_1ms.c*********************************************
Auteur : Julien MAURAT
Date : 24 déc. 2013
Description : 
Constantes :
Fonctions :
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
	//gestion asserv
}
