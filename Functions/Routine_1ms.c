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
	signed long Cons_droite=0;
	signed long Cons_gauche=0;
	//gestion codeurs
	lectureCodeursSigned(&Codeur_d,&Codeur_g);
	//gestion odoetrie
	Gestion_Odometrie_LL(Codeur_d,Codeur_g);
	//gestion asserv
	Gestion_Asserv_HL(Codeur_d,Codeur_g,&Cons_droite,&Cons_gauche);
	controlMotor1_invert(Cons_droite);
	controlMotor2_invert(Cons_gauche);

					printString("cdroite : ");
					printLongVal(Cons_droite);//2147483647);
					printString(" cgauche : ");
					printLongVal(Cons_gauche);//-2147483647);
					UART0_Sendchar('\n');
}
