/**************************Routine_1ms.c*********************************************
Auteur : Julien MAURAT
Date : 24 d�c. 2013
Description : Routine appel�e par l'interruption p�riodique
Constantes : N/A
Fonctions : void routine_1ms(void) : Vas g�rer l'appel au diverses fonction d'odom�trie
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
	if(FLAG_RESET_CODEURS==1)
	{
		resetCodeurs();
		reset_tick_Odometrie();
		Mode_Asserv(MODE_STOP);
		FLAG_RESET_CODEURS=0;
	}
	lectureCodeursSigned(&Codeur_d,&Codeur_g);
	//gestion odoetrie
	Gestion_Odometrie_LL(Codeur_d,Codeur_g);
	//gestion asserv
	Gestion_Asserv_LL(Codeur_d,Codeur_g,&Cons_droite,&Cons_gauche);
	//controlMotor1_invert(Cons_droite);
	//controlMotor2_invert(Cons_gauche);

					printString("cdroite : ");
					printLongVal(Odo_angle*10000);//2147483647);
					printString(" cgauche : ");
					printLongVal(Cons_gauche);//-2147483647);
					UART0_Sendchar('\n');
}
