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
	//gestion du reset codeur

	//IO0SET |= 0x40000000;
	if(FLAG_RESET_CODEURS==1)
	{
		resetCodeurs();
		reset_tick_Odometrie();
		Asserv_Reset_Integrateur();
		Asserv_Reset_Derivateur();
		Asserv_zero=Odo_angle;
		Asserv_Cons_distance = 0;
		Asserv_Cons_angle = 0;
		FLAG_RESET_CODEURS=0;
	}
	//gestion codeurs
	lectureCodeursSigned(&Codeur_d,&Codeur_g);
	//gestion odoetrie
	Gestion_Odometrie_LL(Codeur_d,Codeur_g);
	//gestion asserv
	Gestion_Asserv_LL(Codeur_d,Codeur_g,&Cons_droite,&Cons_gauche);
	controlMotor1_invert(Cons_droite);
	controlMotor2_invert(Cons_gauche);
					/*
					printString("cdroite : ");
					printLongVal(Codeur_d);//2147483647);
					printString(" cgauche : ");
					printLongVal(Codeur_g);//-2147483647);
					printString(" asserv_cons_angle : ");
					printLongVal(Asserv_Cons_angle*1000);//2147483647);
					printString(" Asserv_zero : ");
					printLongVal(Asserv_zero*1000);//-2147483647);

					UART0_Sendchar('\n');*/
					 FLAG_IT_1MS=0;
	//IO0CLR |= 0x40000000;
}
